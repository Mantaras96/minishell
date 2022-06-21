#include "../include/minishell.h"

void get_echo(t_info *info)
{
    int i;
    int flag;

    flag = 0;
    if (!info->pipe_command && !info->redirect)
    {
        i = 1;
        if (!ft_strcmp(info->tokens[1], "-n"))
        {
            flag = 1;
            i++;
        }
        while (info->tokens[i])
        {
            printf("%s", info->tokens[i]);
            i++;
        }
        if (!flag)
           printf("\n");
    }

}