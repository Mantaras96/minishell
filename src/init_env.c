/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerida- <tmerida-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 12:30:54 by tmerida-          #+#    #+#             */
/*   Updated: 2022/08/07 12:32:08 by tmerida-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*init_env2(t_info *info)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	info->envp = set_env("PWD", temp, info->envp, 3);
	free(temp);
	temp = get_env_value("SHLVL", info->envp, 5);
	return (temp);
}

void	init_env(t_info *info, char **argv)
{
	char	*aux;

	(void)argv;
	aux = init_env2(info);
	if (!aux)
	{
		info->envp = set_env("SHLVL", "1", info->envp, 5);
		free(aux);
	}
	else
		info->envp = set_env("SHLVL", ft_itoa(ft_atoi(aux) + 1), info->envp, 5);
	aux = get_env_value("PATH", info->envp, 4);
	if (!aux)
	{
		info->envp = set_env("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", info->envp, 4);
		free(aux);
	}
	aux = get_env_value("_", info->envp, 1);
	if (!aux)
	{
		info->envp = set_env("_", argv[0], info->envp, 1);
		free(aux);
	}
}
