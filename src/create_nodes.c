/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:52:20 by tmerida-          #+#    #+#             */
/*   Updated: 2022/08/16 18:44:18 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_commands	*command_init(void)
{
	t_commands	*commands;

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

static t_list	*stop_fill(t_list *cmds, char **args, char **temp)
{
	ft_lstclear(&cmds, free_content);
	free_matrix(&temp);
	free_matrix(&args);
	return (NULL);
}

static t_commands	*get_params(t_commands *node, char **args[2], int *i)
{
	if (args[0][*i])
	{
		if (args[0][*i][0] == '>' && args[0][*i + 1]
				&& args[0][*i + 1][0] == '>')
			node = get_outfile2(node, args[1], i);
		else if (args[0][*i][0] == '>')
			node = get_outfile1(node, args[1], i);
		else if (args[0][*i][0] == '<' && args[0][*i + 1] && \
			args[0][*i + 1][0] == '<')
			node = get_infile2(node, args[1], i);
		else if (args[0][*i][0] == '<')
			node = get_infile1(node, args[1], i);
		else if (args[0][*i][0] != '|')
			node->full_cmd = add_value_matrix(node->full_cmd, args[1][*i]);
		else
			*i = -2;
		return (node);
	}
	print_error(1, NULL, 2);
	*i = -2;
	return (node);
}

t_list	*create_nodes(char **args, int i)
{
	t_list	*cmds[2];
	char	**temp[2];

	cmds[0] = NULL;
	temp[1] = remove_quotes(args);
	while (args[++i])
	{
		cmds[1] = ft_lstlast(cmds[0]);
		if (i == 0 || (args[i][0] == '|' && args[i + 1]))
		{
			i += args[i][0] == '|';
			ft_lstadd_back(&cmds[0], ft_lstnew(command_init()));
			cmds[1] = ft_lstlast(cmds[0]);
		}
		temp[0] = args;
		cmds[1]->content = get_params(cmds[1]->content, temp, &i);
		if (i < 0)
			return (stop_fill(cmds[0], args, temp[1]));
		if (!args[i])
			break ;
	}
	free_matrix(&temp[1]);
	free_matrix(&args);
	return (cmds[0]);
}
