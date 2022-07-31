
#include "../include/minishell.h"

extern int	g_status;

int is_builtin(t_commands *n)
{
    if (!n->full_cmd)
		return (0);
	if ((n->full_cmd && ft_strchr(*n->full_cmd, '/')) || (n->full_path && \
		ft_strchr(n->full_path, '/')))
		return (0);
    if (!ft_strcmp(*n->full_cmd, "pwd"))
        return (1);
    if (!ft_strcmp(*n->full_cmd, "cd"))
        return (1);
    if (!ft_strcmp(*n->full_cmd, "export"))
        return (1);
    if (!ft_strcmp(*n->full_cmd, "unset"))
        return (1);
    if (!ft_strcmp(*n->full_cmd, "exit"))
        return (1);
    if (!ft_strcmp(*n->full_cmd, "echo"))
        return (1);
    if (!ft_strcmp(*n->full_cmd, "env"))
        return (1);
    return(0);
}

char *find_cmd(char **path, char *cmd, char *full_path)
{
    char *aux;
    int i;
    i = -1;
    full_path = NULL;
    while (path && path[++i])
    {
        free(full_path);
        aux = ft_strjoin(path[i], "/");
        if (!aux)
            return (NULL);
        full_path = ft_strjoin(aux, cmd);
        free(aux);
        if (!full_path)
            return (NULL);
        if (access(full_path, F_OK) == 0)
            break ;
    }
    if (!path || !path[i])
    {
        free(full_path);
        return (NULL);
    } 
    return (full_path);
}

DIR *get_dir(t_info *info, t_list *cmds, char ***s, char *path){
    t_commands *c;
    DIR *dir;
    char **prueba;

    c = cmds->content;
    dir = NULL;
    if (c && c->full_cmd)
        dir = opendir(*c->full_cmd);
    if (c && c->full_cmd && ft_strchr(*c->full_cmd, '/') && !dir)
    {
        *s = ft_split(*c->full_cmd, '/');
        c->full_path = ft_strdup(*c->full_cmd);
        free(c->full_cmd[0]);
        c->full_cmd[0] = ft_strdup(s[0][ft_matrix_len(*s) - 1]);
    }
    else if (!is_builtin(c) && c && c->full_cmd && !dir)
    {
       
        path = get_env_value("PATH", info->envp, 4);
        //printf("path  %s \n", path);
        prueba = ft_split(path, ':');
        free(path);
        c->full_path = find_cmd(prueba, *c->full_cmd, c->full_path);
        if (!c->full_path || !c->full_cmd[0] || !c->full_cmd[0][0])
            printf("Command Not found\n");
    }
    free_matrix(s);
    return (dir);
}

void get_command(t_info *info, t_list *cmds){
    t_commands *c;
    DIR *dir;

    c = cmds->content;
    
    dir = get_dir(info, cmds, NULL, NULL);
    if (!is_builtin(c) && c && c->full_cmd && dir)
        //es un directorio
        write(1, "error\n", 6);
    else if (!is_builtin(c) && c && c->full_path && 
        access(c->full_path, F_OK) == -1)
        //no hay directorio o fichero
        write(1, "error\n", 6);
    else if(!is_builtin(c) && c && c->full_path && 
        access(c->full_path, X_OK) == -1)
        //permission denied
        write(1, "error\n", 6);
    if (dir)
        closedir(dir);
}

void *exec_command(t_info *info, t_list *cmds)
{
    int p_fd[2];

    get_command(info, cmds);
    if(pipe(p_fd) == -1)
        write(1, "pError" , 6);
    if (!validate_fork(info, cmds, p_fd))
       return(NULL);
    close(p_fd[1]);
    if (cmds->next && !((t_commands *)cmds->next->content)->ifile)
        ((t_commands *)cmds->next->content)->ifile = p_fd[0];
    else
        close(p_fd[0]);
    if (((t_commands *)cmds->content)->ifile > 2)
        close (((t_commands *)cmds->content)->ifile);
    if (((t_commands *)cmds->content)->ofile > 2)
        close (((t_commands *)cmds->content)->ofile);
    return (NULL);
}

int builtin(t_info *info, t_list *cmds,  int *num_exit) {
    char **c_full;
   
    while (cmds){
       
        c_full = ((t_commands *)cmds->content)->full_cmd;


        if (c_full && !ft_strcmp (info->tokens[0], "exit"))
            g_status = get_exit(info, num_exit); //Si no funciona probamos con cmd
        else if (!cmds->next && c_full && !ft_strcmp (info->tokens[0], "export"))
            g_status = get_export(info);
        else if (!cmds->next && c_full && !ft_strcmp (info->tokens[0], "cd"))
            g_status = get_cd(info);
        else if (!cmds->next && c_full && !ft_strcmp (info->tokens[0], "unset"))
            g_status = get_unset(info, c_full);
        else {
            exec_command(info, cmds);
        }
        cmds = cmds->next;
    }
    return (g_status);
}

void free_cnt(void *content)
{
    t_commands *node;

    node = content;
    free_matrix(&node->full_cmd);
    free(node->full_path);
    if (node->ifile != STDOUT_FILENO)
        close(node->ifile);
    if (node->ofile != STDOUT_FILENO)
        close(node->ofile);
    free(node);
}

void *check_status(t_info *info, t_list *cmds)
{
    int i;
    int num_exit;

    i = 0;
    num_exit = 0;
    info->cmds = create_nodes(info);
    if (!info->cmds)
        return (info);
    i = ft_lstsize(info->cmds);


    g_status = builtin(info, info->cmds, &num_exit);
    while (i-- > 0)
		waitpid(-1, &g_status, 0);
    if (g_status > 255 )
        g_status = g_status / 255;
    if  (info && num_exit)
    {
        ft_lstclear(&info->cmds, free_cnt);
        return (NULL);
    }
     
    return (info);
    
}

void    *start_args(char *str, t_info *info)
{
    if (!str)
    {
        printf("exit2");
        return(NULL);
    }
    if (str[0] != '\0')
        add_history(str);
    info = check_status(info, info->cmds);
    // if (info && info->cmds)
    //     ft_lstclear(&info->cmds, free_cnt);

    return (info);
}



