/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:42:39 by tmerida-          #+#    #+#             */
/*   Updated: 2022/08/21 12:24:19 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	signal_handler(void)
{
	struct termios	termi;

	if (tcgetattr(STDIN_FILENO, &termi) == -1)
		return (0);
	termi.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termi) == -1)
		return (0);
	if (signal(SIGINT, handler) == SIG_ERR)
		return (0);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (0);
	return (1);
}

void	mini_getpid(t_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		print_error(9, NULL, 1);
		free_matrix(&info->envp);
		exit(1);
	}
	if (!pid)
	{
		free_matrix(&info->envp);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	info->pid = pid - 1;
}

void	init_prompt(t_info *info)
{
	char	*aux;
	char	*str;
	pid_t	pid;
	int		fd[2];

	str = getcwd(NULL, 0);
	aux = ft_strjoin("\033[1;33m", str);
	free(str);
	info->prompt = ft_strjoin(aux, "--ENCUERAO🦄🦹--->$ \033[1;00m");
	init_pid(fd, pid);
	info->input = readline(info->prompt);
	free(aux);
	free(info->prompt);
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
