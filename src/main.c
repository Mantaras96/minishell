/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 00:29:16 by albertmanta       #+#    #+#             */
/*   Updated: 2022/05/27 18:35:20 by amantara         ###   ########.fr       */
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


int main(int argc, char **argv, char **envp)
{
	char *input;

	(void)argc;
	(void)argv;
	(void)envp;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		input = readline("ENCUERAO🦄🦹-->$ ");
		if (input)
		{
			if(!ft_strcmp(input, "pwd"))
				get_pwd();
		}else
			exit (1);
	}
}