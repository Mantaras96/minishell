/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:25:53 by amantara          #+#    #+#             */
/*   Updated: 2022/08/06 15:29:00 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	word_no_quotes(char *token)
{
	int	count;
	int	i;
	int	dquote;
	int	squote;

	i = 0;
	count = 0;
	dquote = 0;
	squote = 0;
	while (token && token[i])
	{
		squote = (squote + (!dquote && token[i] == '\'')) % 2;
		dquote = (dquote + (!squote && token[i] == '\"')) % 2;
		if ((token[i] == '\"' && !squote) || (token[i] == '\'' && !dquote))
			count++;
		i++;
	}
	if (squote || dquote)
		return (-1);
	return (count);
}

char	*remove_quotes_token(char *token, int s_quote, int d_quote)
{
	int		i[2];
	char	*trimmed;

	i[1] = -1;
	i[0] = 0;
	trimmed = malloc(sizeof (char)
			* (ft_strlen(token) - word_no_quotes(token) + 1));
	while (token[i[0]])
	{
		s_quote = (s_quote + (!d_quote && token[i[0]] == '\'')) % 2;
		d_quote = (d_quote + (!s_quote && token[i[0]] == '\"')) % 2;
		if ((token[i[0]] != '\"' || s_quote)
			&& (token[i[0]] != '\'' || d_quote) && ++i[1] >= 0)
			trimmed[i[1]] = token[i[0]];
		i[0]++;
	}
	trimmed[++i[1]] = '\0';
	return (trimmed);
}

char	**remove_quotes(char **tokens)
{
	char	**n_tokens;
	char	*aux;
	int		i;

	n_tokens = ft_strdup_matrix(tokens);
	i = 0;
	while (n_tokens && n_tokens[i])
	{
		aux = remove_quotes_token(n_tokens[i], 0, 0);
		free(n_tokens[i]);
		n_tokens[i] = aux;
		i++;
	}
	return (n_tokens);
}
