/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerida- <tmerida-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:10:39 by tmerida-          #+#    #+#             */
/*   Updated: 2022/08/06 16:18:39 by tmerida-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	go_home(t_info *info)
{
	char	*path;

	g_status = 0;
	path = get_env_value("HOME", info->envp, 4);
	if (chdir(path))
	{
		printf("%s%s\n", info->tokens[0], ": HOME not set");
		g_status = 1;
	}
	update_pwd(info);
	free(path);
	return (g_status);
}

int	go_last(t_info *info)
{
	char	*path;

	g_status = 0;
	path = get_env_value("OLDPWD", info->envp, 6);
	chdir(path);
	free(path);
	update_pwd(info);
	return (g_status);
}

int	go_path(t_info *info)
{
	g_status = 0;
	if (chdir(info->tokens[1]))
	{
		printf("%s%s%s\n", info->tokens[0],
			": no such file or directory: ", info->tokens[1]);
		g_status = 1;
	}
	update_pwd(info);
	return (g_status);
}

void	update_pwd(t_info *info)
{
	char	*pwd;
	char	*oldpwd;

	oldpwd = get_env_value("PWD", info->envp, 3);
	pwd = getcwd(NULL, 0);
	info->envp = set_env("OLDPWD", oldpwd, info->envp, 6);
	info->envp = set_env("PWD", pwd, info->envp, 3);
	free(pwd);
	free(oldpwd);
}

int	get_cd(t_info *info)
{
	if ((!ft_strcmp(info->tokens[0], "cd") && info->counter == 1)
		|| (!ft_strcmp(info->tokens[1], "~") && info->counter == 2))
		g_status = go_home(info);
	else if (!ft_strcmp(info->tokens[1], "..") && info->counter == 2)
	{
		chdir("..");
		update_pwd(info);
	}
	else if (!ft_strcmp(info->tokens[1], "-") && info->counter == 2)
		g_status = go_last(info);
	else
		g_status = go_path(info);
	return (g_status);
}
