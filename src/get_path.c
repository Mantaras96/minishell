#include "../include/minishell.h"

extern int	g_status;

void get_path(t_info *info)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
        perror("Fork: ");
    if (pid == 0)
    {
        if (access(info->tokens[0], 0) == 0)
            execve(info->tokens[0], info->tokens, info->envp);
        else
        {
            perror("Error");
            g_status = 127;
            exit(127);
        }
    }
    waitpid(pid, NULL, 0);
}

char *validate_command(char **paths, char *command)
{
    char *aux;
    int i;

    i = -1;
    while(paths[++i])
    {
        aux = ft_strjoin(paths[i], "/");
        aux = ft_strjoin(aux, command);
        if (access(aux, 0) == 0)
            return (aux);
        free(aux);
    }
    return (NULL);
}

void get_other(t_info *info)
{
    char **path;
    char *cmd;
    char *path_value;
    int i;

    i = 0;
    path_value = get_env_value("PATH", info->envp, 4);
    path = ft_split(path_value, ':');
    cmd = validate_command(path, info->tokens[0]);
    if (!cmd)
    {
        free(cmd);
        free(path);
        printf("COMMAND NOT FOUND ENCUERATE \n");
    }
    execve(cmd, info->tokens, info->envp);

}


void execute_other_commands(t_info *info)
{
    pid_t  pid;

    pid = fork();
    if (pid < 0)
        perror("Fork: ");
    if (pid == 0)
        get_other(info);
    waitpid(pid, NULL, 0);
}