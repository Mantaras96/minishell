/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:43:32 by amantara          #+#    #+#             */
/*   Updated: 2022/08/06 16:44:21 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_split	start_split(void)
{
	t_split	split;

	split.comillas = 0;
	split.i = 0;
	split.j = 0;
	split.k = 0;
	split.size = 0;
	return (split);
}
