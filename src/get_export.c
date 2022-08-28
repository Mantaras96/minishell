/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:45:20 by amantara          #+#    #+#             */
/*   Updated: 2022/08/06 15:46:07 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	var_in_envp(char *argv, char **envp, int *j)
{
	int	pos;
	int	i;

	i = 0;
	*j = 0;
	pos = ft_strchr_i(argv, 61);
	if (pos == -1)
		return (-1);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], argv, pos + 1))
		{
			*j = i;
			return (1);
		}  
		i++;
	}
	*j = i;
	return (0);
}

int	search_value_string(char *argv, int value)
{
	int	i;

	i = 0;
	if (!argv)
		return (-1);
	while (argv[i])
	{
		if (argv[i] == (unsigned char)value)
			return (i);
		i++;
	}
	if ((unsigned char)value == '\0')
		return (i);
	return (-1);
}

int	get_export(t_info *info)
{
	int		i;
	int		j;
	int		pos;
	char	**argv;

	i = 1;
	j = 0;
	argv = ((t_commands *)info->cmds->content)->full_cmd;
	// while (argv[j])
	// {
	// 	printf("Export: %s\n", argv[j]);
	// 	j++;
	// }
	if (info->counter >= 2)
	{
		while (i < info->counter)
		{
			pos = count_var_envp(argv[i], info->envp, &j);
			if (pos == 1)
			{
				free(info->envp[j]);
				info->envp[j] = ft_strdup(argv[i]);
			}
			else if (!pos)
				info->envp = add_value_matrix(info->envp, argv[i]);
		i++;
		}
	}
	return (0);
}

int	count_var_envp(char *token, char **envp, int *j)
{
	int	aux;
	int	i;

	i = 0;
	aux = search_value_string(token, '=');
	if (!aux)
		return (-1);
	while (i < ft_matrix_len(envp) - 1)
	{
		if (!ft_strncmp(envp[i], token, aux + 1))
			return (1);
		i++;
		*j = i;
	}
	return (0);
}

int	get_unset(t_info *info, char **full_cmd)
{
	int		i;
	int		j;
	char	*aux;

	i = 1;
	j = 0;
	if (full_cmd[i])
	{
		while (full_cmd[i])
		{
			if (full_cmd[i][ft_strlen(full_cmd[i]) - 1] != '=')
			{
				aux = ft_strjoin(full_cmd[i], "=");
				free(full_cmd[i]);
				full_cmd[i] = aux;
			}
			if (var_in_envp(full_cmd[i], info->envp, &j))
				info->envp = ft_matrix_replace_in(&info->envp, NULL, j);
			i++;
		}
	}
	return (0);
}
