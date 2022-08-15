/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 12:30:54 by tmerida-          #+#    #+#             */
/*   Updated: 2022/08/15 16:27:12 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*init_env2(t_info *info)
{
	char	*temp;
	char	*num;

	temp = getcwd(NULL, 0);
	info->envp = set_env("PWD", temp, info->envp, 3);
	free(temp);
	temp = get_env_value("SHLVL", info->envp, 5);
	if (!temp)
	{
		num = ft_strdup("1");
		info->envp = set_env("SHLVL", num, info->envp, 5);
	}
	else
	{
		num = ft_itoa(ft_atoi(temp) + 1);
		info->envp = set_env("SHLVL", num, info->envp, 5);
	}
	free(temp);
	free (num);
}

void	init_env(t_info *info, char **argv)
{
	char	*aux;

	(void)argv;
	init_env2(info);
	aux = get_env_value("PATH", info->envp, 4);
	if (!aux)
	{
		aux = "/usr/local/sbin:/usr/local/bin:/usr/bin:/bin";
		info->envp = set_env("PATH", aux, info->envp, 4);
	}
	free(aux);
	aux = get_env_value("_", info->envp, 1);
	if (!aux)
		info->envp = set_env("_", argv[0], info->envp, 1);
	free(aux);
}
