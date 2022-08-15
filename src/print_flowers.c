/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flowers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:29:44 by amantara          #+#    #+#             */
/*   Updated: 2022/08/15 13:39:40 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_star_minishell(void)
{
	int		fd;
	int		i;
	char	*aux;

	i = 0;
	fd = open("./assets/flor.txt", O_RDONLY);
	while (i < 5)
	{
		aux = get_next_line(fd);
		ft_printf("%s", aux);
		i++;
		free(aux);
	}
	close(fd);
}
