/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:25:33 by tmerida-          #+#    #+#             */
/*   Updated: 2022/08/20 11:54:56 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	get_exit(t_info *info, int *num_exit)
{
	int			ret;
	t_commands	*node;

	node = info->cmds->content;
	*num_exit = !info->cmds->next;
	if (*num_exit)
		ft_putstr_fd("exit\n", 2);
	if (!node->full_cmd || !node->full_cmd[1])
		return (0);
	ret = ft_atoi(node->full_cmd[1]);
	if (ret == -1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(node->full_cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	else if (ft_matrix_len(node->full_cmd) > 2)
	{
		*num_exit = 0;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	ret %= 256 + 256 * (ret < 0);
	return (ret);
}
