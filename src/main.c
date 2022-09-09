/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:38:08 by tmerida-          #+#    #+#             */
/*   Updated: 2022/08/16 18:42:05 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status;

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		g_status = 1;
		printf("\n");
		rl_replace_line("", 1);
	}
	else if (signum == SIGQUIT)
	{
		rl_replace_line("", 0);
	}
	rl_on_new_line();
	rl_redisplay();
}

void	handler_bloking(int signum)
{
	(void)signum;
	printf("^C\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_status = 130;
}

void	handler_counter(int sig_num)
{
	printf("^\\Quit: %d\n", sig_num);
	g_status = 131;
}

void	prepare_signals_blocked(void)
{
	signal(SIGINT, handler_bloking);
	signal(SIGQUIT, handler_counter);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	(void)argc;
	info = (t_info *)malloc(sizeof(t_info));
	init_info(info, envp, argv);
	while (42)
	{
		if (signal_handler() == 0)
			return (0);
		init_prompt(info);
		if (!start_args(info->input, info))
			break ;
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
	}
	exit(g_status);
}
