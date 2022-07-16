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

void	free_content(void *content)
{
	t_commands	*node;

	node = content;
	free_matrix(&node->full_cmd);
	free(node->full_path);
	if (node->ifile != STDIN_FILENO)
		close(node->ifile);
	if (node->ofile != STDOUT_FILENO)
		close(node->ofile);
	free(node);
}

static t_list	*stop_fill(t_list *cmds, t_info *info, char **temp)
{
	ft_lstclear(&cmds, free_content);
	free_matrix(&temp);
	free_matrix(&info->tokens);
	return (NULL);
}  

static t_commands *get_params(t_commands *node, char **temp1, char **temp2, int *i)
{
    if (temp1[*i])
	{
		if (temp1[*i][0] == '>' && temp1[*i + 1] && temp1[*i + 1][0] == '>')
			node = get_outfile2(node, temp2, i);
		else if (temp1[*i][0] == '>')
			node = get_outfile1(node, temp2, i);
		else if (temp1[*i][0] == '<' && temp1[*i + 1] && \
			temp1[*i + 1][0] == '<')
			node = get_infile2(node, temp2, i);
		else if (temp1[*i][0] == '<')
			node = get_infile1(node, temp2, i);
		else if (temp1[*i][0] != '|')
			node->full_cmd = add_value_matrix(node->full_cmd, temp2[*i]);
		else
		{
			//mini_perror(10, NULL, 2);
			*i = -2;
		}
		return (node);
	}
	//mini_perror(10, NULL, 2);
	*i = -2;
	return (node);
}


t_list *create_nodes(t_info *info)
{
    t_list *cmd_1;
    t_list *cmd_2;
    int i;
    char **temp1;
    char **temp2;

    i = 0;
    cmd_1 = NULL;
    temp2 = info->tokens;

    while (info->tokens[i])
    {
        cmd_2 = ft_lstlast(cmd_1);
        if (i == 0 || (info->tokens[i][0] == '|' && info->tokens[i + 1]))
        {
            i += info->tokens[i][0] == '|';
            ft_lstadd_back(&cmd_1, ft_lstnew(command_init()));
            cmd_2 = ft_lstlast(cmd_1);
        }
        temp1 = info->tokens;
        cmd_2->content = get_params(cmd_2->content, temp1, temp2, &i);
        if (i < 0)
			return(stop_fill(cmd_1, info, temp2));
		if (!info->tokens[i])
			break ;
        i++;
    }
    //free_matrix(&temp2);
	return(cmd_1);
}