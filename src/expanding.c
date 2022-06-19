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

	printf("Teo string: %s\n", str);
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



char	*expand_vars(char *str, int i, int quotes[2], t_info *info)
{
	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && str[i] == '$' && str[i + 1] && \
			((ft_strchars_i(&str[i + 1], "/~%^{}:; ") && !quotes[1]) || \
			(ft_strchars_i(&str[i + 1], "/~%^{}:;\"") && quotes[1])))
			return (expand_vars(get_substr_var(str, ++i, info), -1, \
				quotes, info));
	}
	return (str);
}

int expanding (t_info *info) {
	int i;
	int		quotes[2];

	i = 0;
	while (info->tokens && info->tokens[i]){
		info->tokens[i] = expand_vars(info->tokens[i], -1, quotes, info);
		info->tokens[i] = expand_home(info->tokens[i], -1, quotes, info);
		printf("String parseada: %s\n", info->tokens[i]);
		i++;
	}

	return (0);
}

char	*expand_home(char *str, int i, int quotes[2], t_info *info){
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
			path = ft_strjoin(aux, get_env_value("HOME", info->envp, 4));
			free(aux);
			aux = ft_substr(str, i + 1, ft_strlen(str));
			free(str);
			str = ft_strjoin(path, aux);
			free(aux);
			free(path);
			return (expand_home(str, i + ft_strlen(get_env_value("HOME", info->envp, 4)) - 1, quotes, info));
		}
	}
	return (str);

}