#include "../include/minishell.h"

extern int	g_status;

void *redir_process(t_list *cmd, int fd[2]){

    t_commands *c;

    c = cmd->content;
    if (c->ifile != STDIN_FILENO){
        if (dup2(c->ifile, STDIN_FILENO) == -1)
            write (1, "Mini perror", 11);
        close (c->ofile);
    }
    else if (cmd->next && dup2(fd[1], STDOUT_FILENO) == -1)
        write (1, "Mini perror", 11);
    close(fd[1]);
    return ("");
}

void    builtin_process(t_info *info, t_list *cmds, t_commands *c){
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    if (!is_builtin(c) && c->full_cmd)
        execve(c->full_path, c->full_cmd, info->envp);
    else if (c->full_cmd && !ft_strcmp(*c->full_cmd, "pwd"))
        get_pwd();
     else if (c->full_cmd && !ft_strcmp(*c->full_cmd, "echo"))
        get_echo(info);
        //write(1, "hola", 4);
    else if (c->full_cmd && !ft_strcmp(*c->full_cmd, "env"))
        get_env(info);
        //write(1, "hola", 4);
        
}


void *child_process(t_info *info, t_list *cmds, int p_fd[2])
{
    t_commands *c;

    c = cmds->content;
    redir_process(cmds, p_fd);
    close(p_fd[0]);
    builtin_process(info, cmds, c);
    //ft_lstclear(&info->cmds, free_content);
    exit(g_status);
}

void exc_fork(t_info *info, t_list *cmds, int p_fd[2])
{
    pid_t pid;
    pid = fork();
    if(pid < 0)
    {
        close(p_fd[0]);
        close(p_fd[1]);
        //error de forks
    }
    else if (!pid)
        child_process(info, cmds, p_fd);
}

void *validate_fork(t_info *info, t_list *cmds, int p_fd[2])
{
    DIR *dir;
    t_commands *c;

    c = cmds->content;
    dir = NULL;
    if (c->full_cmd)
        dir = opendir(*c->full_cmd);
    if (c->ifile == -1 || c->ofile == -1)
        return (NULL);
    if ((c->full_path && access(c->full_path, X_OK) == 0) || is_builtin(c))
        exc_fork(info, cmds, p_fd);
    else if (!is_builtin(c) && ((c->full_path && \
        !access(c->full_path, F_OK)) || dir))
        g_status = 126;
    else if (!is_builtin(c) && c->full_cmd)
        g_status = 127;
    if (dir)
        closedir(dir);
    return ("");
}