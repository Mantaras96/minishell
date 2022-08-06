/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerida- <tmerida-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:20:25 by tmerida-          #+#    #+#             */
/*   Updated: 2022/08/06 16:25:25 by tmerida-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**set_env(char *var, char *value, char **envp, int n)
{
	int		i;
	int		j;
	char	*aux1;

	if (n < 0)
		n = ft_strlen(var);
	i = -1;
	aux1 = ft_strjoin(var, "=");
	aux1 = ft_strjoin(aux1, value);
	while (++i < ft_matrix_len(envp))
	{
		j = n;
		if (j < search_value_string(envp[i], '='))
		{
			j = search_value_string(envp[i], '=');
		}
		if (!ft_strncmp(envp[i], var, j))
		{
			envp[i] = aux1;
			return (envp);
		}
	}
	envp = add_value_matrix(envp, aux1);
	free(aux1);
	return (envp);
}

char	*get_env_value(char *var, char **envp, int n)
{
	int	i;
	int	j;

	if (n < 0)
		n = ft_strlen(var);
	i = 0;
	while (!ft_strchr(var, '=') && envp && envp[++i])
	{
		j = n;
		if (j < search_value_string(envp[i], '='))
			j = search_value_string(envp[i], '=');
		if (!ft_strncmp(envp[i], var, j))
		{
			return (ft_substr(envp[i], j + 1, ft_strlen(envp[i])));
		}
	}
	return (NULL);
}

int	get_env(t_info *info)
{
	int	i;

	i = 0;
	while (info->envp[i])
	{
		printf("%s\n", info->envp[i]);
		i++;
	}
	return (0);
}
