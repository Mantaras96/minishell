/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:41:07 by tmerida-          #+#    #+#             */
/*   Updated: 2022/08/20 11:49:23 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	builtin(t_info *info, t_list *cmds, int *num_exit)
{
	char	**c_full;

	while (cmds)
	{
		c_full = ((t_commands *)cmds->content)->full_cmd;
		if (c_full && !ft_strcmp (c_full[0], "exit"))
			g_status = get_exit(info, num_exit);
		else if (!cmds->next && c_full && !ft_strcmp(c_full[0], "export"))
			g_status = get_export(info);
		else if (!cmds->next && c_full && !ft_strcmp(c_full[0], "cd"))
			g_status = get_cd(info);
		else if (!cmds->next && c_full && !ft_strcmp(c_full[0], "unset"))
			g_status = get_unset(info, c_full);
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			exec_command(info, cmds);
		}
		cmds = cmds->next;
	}
	return (g_status);
}

void	free_cnt(void *content)
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

void	*check_status(t_info *info, t_list *cmds, char **args)
{
	int			i;
	int			num_exit;

	num_exit = 0;
	(void)cmds;
	info->cmds = create_nodes(args, -1);
	if (!info->cmds)
		return (info);
	i = ft_lstsize(info->cmds);
	g_status = builtin(info, info->cmds, &num_exit);
	while (i-- > 0)
		waitpid(-1, &g_status, 0);
	if (!num_exit && g_status == 1)
		g_status = 0;
	if (g_status > 255)
		g_status = g_status / 255;
	if (args && num_exit)
	{
		ft_lstclear(&info->cmds, free_cnt);
		return (NULL);
	}
	return (info);
}

void	*start_args(char *str, t_info *info)
{
	char	**args;

	if (!str)
	{
		printf("exit\n");
		return (NULL);
	}
	if (str[0] != '\0')
		add_history(str);
	args = parsing(info);
	free(str);
			int j = 0;
		while (args[j])
		{
			printf("Temp: %s\n", args[j]);
			j++;
		}
	if (args != NULL)
	{
		args = expanding(info, args);
		info = check_status(info, info->cmds, args);
		if (info && info->cmds)
			ft_lstclear(&info->cmds, free_cnt);
	}
	return (info);
}
