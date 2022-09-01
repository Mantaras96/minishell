/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerida- <tmerida-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:18:47 by tmerida-          #+#    #+#             */
/*   Updated: 2022/08/06 16:20:17 by tmerida-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_echo(t_commands *info)
{
	int	i;
	int	flag;

	i = 1;
	flag = 1;
	if (!ft_strncmp(info->full_cmd[1], "-n", 2))
	{
		flag = 0;
		i = 2;
	}
	while (info->full_cmd && info->full_cmd[i])
	{
		ft_putstr_fd(info->full_cmd[i], 1);
		i++;
		if (info->full_cmd[i])
			ft_putchar_fd(' ', 1);
	}
	return (write(1, "\n", flag) == 2);
}
