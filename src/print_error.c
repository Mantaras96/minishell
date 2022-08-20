/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:01:43 by amantara          #+#    #+#             */
/*   Updated: 2022/08/20 12:05:50 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

void	*print_error(int c_err, char *param, int err)
{
	if (c_err == 1)
		ft_putstr_fd("minishell: command not found: ", 2);
	g_status = err;
	ft_putendl_fd(param, 2);
	return (NULL);
}
