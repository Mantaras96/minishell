/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:32:35 by amantara          #+#    #+#             */
/*   Updated: 2022/08/21 12:31:16 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	start_parsing(t_info *info)
{
	int	i;

	i = -1;
	while (info->input[++i])
	{
		if (info->input[i] == 34)
			info->doubles++;
		else if (info->input[i] == 39)
			info->simples++;
	}
	if (info->doubles > 0 && info->doubles % 2 == 1)
	{
		print_error(2, NULL, 1);
		info->simples = 0;
		info->doubles = 0;
		return (0);
	}
	if (info->simples > 0 && info->simples % 2 == 1)
	{
		print_error(2, NULL, 1);
		info->simples = 0;
		info->doubles = 0;
		return (0);
	}
	return (1);
}

char	**parsing(t_info *info)
{
	if (start_parsing(info))
	{
		info->counter = 0;
		info->simples = 0;
		info->doubles = 0;
		return (create_tokens(info));
	}
	return (NULL);
}
