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
		g_status = 130;
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

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;
	char	*str;
	char	*out;

	(void)argc;
	info = (t_info *)malloc(sizeof(t_info));
	init_info(info, envp, argv);
	if (signal_handler() == 0)
		return (0);
	while (42)
	{
		init_prompt(info);
		if (!start_args(info->input, info))
			break ;
	}
	exit(g_status);
}
