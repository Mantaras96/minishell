/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerida- <tmerida-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:38:08 by tmerida-          #+#    #+#             */
/*   Updated: 2022/08/06 16:40:36 by tmerida-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status;

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
	}
	else if (signum == SIGQUIT)
		rl_on_new_line();
	rl_on_new_line();
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	(void)argc;
	info = (t_info *)malloc(sizeof(t_info));
	init_info(info, envp, argv);
	if (signal_handler() == 0)
		return (0);
	while (argv && argc)
	{
		init_prompt(info);
		info->input = readline(info->prompt);
		if (info->input)
		{
			if (parsing(info))
			{
				expanding(info);
				if (!start_args(info->input, info))
					break ;
			}
		}
		else
			exit (1);
		free(info->input);
	}
	exit(g_status);
}
