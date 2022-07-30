#include "../include/minishell.h"

void get_echo(t_commands *info)
{
    int i;
    int flag;
    t_commands *commands;
    char **full_cmd;

    full_cmd = info->full_cmd;

    i = 0;
    while (full_cmd && full_cmd[i]){
        printf("Linea: %s", full_cmd[i]);
        i++;
    }


}