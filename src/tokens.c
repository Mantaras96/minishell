/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertmantaras <albertmantaras@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:21:46 by amantara          #+#    #+#             */
/*   Updated: 2022/08/29 23:26:48 by albertmanta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_words(const char *s, char *c, int i[2])
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (s[i[0]] != '\0')
	{
		if (!ft_strchr(c, s[i[0]]))
		{
			i[1]++;
			while ((!ft_strchr(c, s[i[0]]) || q[0]) && s[i[0]] != '\0')
			{
				if (!q[1] && (s[i[0]] == '\"' || s[i[0]] == '\''))
					q[1] = s[i[0]];
				q[0] = (q[0] + (s[i[0]] == q[1])) % 2;
				q[1] *= q[0] != 0;
				i[0]++;
			}
			if (q[0])
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}

// a_split: Array with malloc nwords.
char	**ft_split_all(char *str, char **a_split)
{
	t_split	split;
	int		s_len;

	split = start_split();
	s_len = ft_strlen(str);
	while (str[split.i])
	{
		while (ft_strchr(" ", str[split.i]) && str[split.i] != '\0')
			split.i++;
		split.j = split.i;
		while ((!ft_strchr(" ", str[split.i]) || split.q_1 || split.q_2)
			&& str[split.i])
		{
			split.q_1 = (split.q_1 + (!split.q_2 && str[split.i] == '\'')) % 2;
			split.q_2 = (split.q_2 + (!split.q_1 && str[split.i] == '\"')) % 2;
			split.i++;
		}
		if (split.j >= s_len)
			a_split[split.k++] = "\0";
		else
			a_split[split.k++] = ft_substr(str, split.j, split.i - split.j);
	}
	return (a_split);
}

char	**create_tokens(t_info *info)
{
	char	**str;
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	info->counter = count_words(info->input, " ", i);
	str = malloc((info->counter + 1) * sizeof(char *));
	str = ft_split_all(info->input, str);
	str[info->counter] = NULL;
	return (str);
}
