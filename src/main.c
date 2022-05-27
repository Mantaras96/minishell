/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 00:29:16 by albertmanta       #+#    #+#             */
/*   Updated: 2022/05/27 17:13:40 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <fcntl.h>

int main(){
	int		fd;
	char	*aux;
	int		i = 0;
	char *input;

	fd = open("./assets/flor.txt", O_RDONLY);
	while (i < 5)
	{
		aux = get_next_line(fd);
		ft_printf("%s", aux);
		i++;
	}
	
	while (42)
	{
		input = readline("ENCUERAO🦄🦹>$ ");	
	}
	close(fd);
	return (0);
}