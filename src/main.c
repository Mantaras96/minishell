/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 00:29:16 by albertmanta       #+#    #+#             */
/*   Updated: 2022/05/27 17:42:54 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <fcntl.h>

void handler(int signum)
{
	if(signum == SIGINT){
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}


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
	close(fd);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		input = readline("ENCUERAO🦄🦹-->$ ");
		if (input)
		{
			if(!ft_strncmp(input, "pwd"))
				get_pwd();
		}else
			exit (1);
	}
}