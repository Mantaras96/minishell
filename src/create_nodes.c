#include "../include/minishell.h"

t_commands *command_init(void)
{
    t_commands *commands;
    commands = malloc(sizeof(t_commands));
    if (!commands)
        return (NULL);
    commands->full_cmd = NULL;
    commands->full_path = NULL;
    commands->ifile = STDIN_FILENO;
    commands->ofile = STDOUT_FILENO;
    return (commands);
}


t_list create_nodes(t_info *info)
{
    t_list *cmd_1;
    t_list *cmd_2;
    int i;
    char **temp1;
    char **temp2;

    i = 0;
    cmd_1 = NULL;
    temp2 == info->tokens;

    while (info->tokens[i])
    {
        cmd_2 = ft_lstlast(cmd_1);
        if (i == 0 || (info->tokens[i][0] == '|' && info->tokens[i + 1]))
        {
            i += info->tokens[i][0] == '|';
            ft_lstadd_back(&cmd_1, ft_lstnew(command_init()));
            cmd_2 = ft_lstlast(cmd_1);
        }
        i++;
    }


    return (cmd_1);
}