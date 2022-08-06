/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:23:53 by amantara          #+#    #+#             */
/*   Updated: 2022/08/06 15:23:55 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

/* Si encontramos un pipe enviaremos un 1 se mantiene a 0 sino */
int	check_pipe_command(t_info *info)
{
	int	i;

	i = 0;
	info->pipe_command = 0;
	while (info->tokens[i])
	{
		if (info->tokens[i][0] == '|')
		{
			info->pipe_command = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	start_minishell(t_info *info)
{
	start_no_pipe(info);
}
