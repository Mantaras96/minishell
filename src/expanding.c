/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerida- <tmerida-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:06:12 by tmerida-          #+#    #+#             */
/*   Updated: 2022/08/06 16:10:21 by tmerida-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	ft_strchars_i(const char *s, char *set)
{
	int				i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		if (ft_strchr(set, s[i]))
			return (i);
		i++;
	}
	return (-1);
}

static char	*get_substr_var(char *str, int i, t_info *prompt)
{
	char	*aux;
	int		pos;
	char	*path;
	char	*var;

	pos = ft_strchars_i(&str[i], "|\"\'$?>< ") + (ft_strchr("$?", str[i]) != 0);
	if (pos == -1)
		pos = ft_strlen(str) - 1;
	aux = ft_substr(str, 0, i - 1);
	var = get_env_value(&str[i], prompt->envp, \
		ft_strchars_i(&str[i], "\"\'$|>< "));
	if (!var && str[i] == '$')
		var = ft_itoa(prompt->pid);
	else if (!var && str[i] == '?')
		var = ft_itoa(g_status);
	path = ft_strjoin(aux, var);
	free(aux);
	aux = ft_strjoin(path, &str[i + pos]);
	free(var);
	free(path);
	free(str);
	return (aux);
}

char	*expand_vars(char *str, int i, t_info *info)
{
	int	q_simples;
	int	q_doubles;

	q_simples = 0;
	q_doubles = 0;
	while (str && str[++i])
	{
		q_simples = (q_simples + (!q_doubles && str[i] == '\'')) % 2;
		q_doubles = (q_doubles + (!q_simples && str[i] == '\"')) % 2;
		if (!q_simples && str[i] == '$' && str[i + 1] && \
			((ft_strchars_i(&str[i + 1], "/~%^{}:; ") && !q_doubles) || \
			(ft_strchars_i(&str[i + 1], "/~%^{}:;\"") && q_doubles)))
			return (expand_vars(get_substr_var(str, ++i, info), -1, info));
	}
	return (str);
}

char	**expanding(t_info *info, char **args)
{
	char	**aux;
	int		i;
	int		quotes[2];

	i = 0;
	while (args && args[i])
	{
		args[i] = expand_vars(args[i], -1, info);
		args[i] = expand_home(args[i], -1, quotes, info, get_env_value("HOME", info->envp, 4));
		aux = ft_cmdsubsplit(args[i], "><|");
		ft_matrix_replace_in(&args, aux, i);
		i += ft_matrix_len(aux) - 1;
		free_matrix(&aux);
		i++;
	}
	return (args);
}

char	*expand_home(char *str, int i, int quotes[2], t_info *info, char *home)
{
	char	*path;
	char	*aux;

	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && !quotes[1] && str[i] == '~' && (i == 0 || \
			str[i - 1] != '$'))
		{
			aux = ft_substr(str, 0, i);
			path = ft_strjoin(aux, home);
			free(aux);
			aux = ft_substr(str, i + 1, ft_strlen(str));
			free(str);
			str = ft_strjoin(path, aux);
			free(aux);
			free(path);
			return (expand_home(str, i + ft_strlen(home) - 1, quotes, info, home));
		}
	}
	free(home);
	return (str);
}
