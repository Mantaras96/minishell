/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:01:43 by amantara          #+#    #+#             */
/*   Updated: 2022/08/21 12:48:32 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

void	*print_error(int c_err, char *param, int err)
{
	if (c_err == 1)
		ft_putstr_fd("minishell: command not found: ", 2);
	else if (c_err == 2)
		ft_putstr_fd("minishell: Quotes not closed: ", 2);
	else if (c_err == 3)
		ft_putstr_fd("minishell: Is a directory: ", 2);
	else if (c_err == 4)
		ft_putstr_fd("minishell: Is not a directory: ", 2);
	else if (c_err == 5)
		ft_putstr_fd("minishell: Permission denied: ", 2);
	else if (c_err == 6)
		ft_putstr_fd("minishell: Error generating pipe: ", 2);
	else if (c_err == 7)
		ft_putstr_fd("minishell: Error getting PID program: ", 2);
	else if (c_err == 8)
		ft_putstr_fd("minishell: sintax error: ", 2);
	else if (c_err == 9)
		ft_putstr_fd("minishell: Error fork ", 2);
	else if (c_err == 10)
		ft_putstr_fd("minishell: DUP error: ", 2);
	g_status = err;
	ft_putendl_fd(param, 2);
	return (NULL);
}
