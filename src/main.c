/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertmantaras <albertmantaras@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 00:29:16 by albertmanta       #+#    #+#             */
/*   Updated: 2022/05/26 01:01:02 by albertmanta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <fcntl.h>

int main(){
	int		fd;
	char	*aux;
	int		i = 0;

	fd = open("/Users/albertmantaras/minishell/assets/flor.txt", O_RDONLY);
	while (i < 5)
	{
		aux = get_next_line(fd);
		ft_printf("%s", aux);
		i++;
	}
	close(fd);
	return (0);
}