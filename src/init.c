/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerida- <tmerida-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:42:39 by tmerida-          #+#    #+#             */
/*   Updated: 2022/08/06 16:48:05 by tmerida-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status;

int	signal_handler(void)
{
	struct termios	termi;

	if (tcgetattr(STDIN_FILENO, &termi) == -1)
	{	
		printf("salir");
		return (0);
	}
	termi.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termi) == -1)
		return (0);
	if (signal(SIGINT, handler))
		return (0);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (0);
	return (1);
}

void	mini_getpid(t_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0 || !pid)
		exit(1);
	waitpid(pid, NULL, 0);
	info->pid = pid - 1;
}

void	init_prompt(t_info *info)
{
	char	*aux;
	pid_t	pid;
	int		fd[2];

	aux = ft_strjoin("\033[1;33m", getcwd(NULL, 0));
	info->prompt = ft_strjoin(aux, "--ENCUERAO🦄🦹--->$ \033[1;00m");
	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exit (1);
	}
	close(fd[1]);
	waitpid(pid, NULL, 0);
	close(fd[0]);
}

void	init_info(t_info *info, char **envp, char **argv)
{	
	info->doubles = 0;
	info->simples = 0;
	info->counter = 0;
	info->words = 0;
	info->redirect = 0;
	info->envp = ft_strdup_matrix(envp);
	mini_getpid(info);
	init_env(info, argv);
	print_star_minishell();
}
