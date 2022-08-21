/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:21:46 by amantara          #+#    #+#             */
/*   Updated: 2022/08/21 12:37:20 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_space(char c, int comillas)
{
	if (!comillas)
	{
		if (c == ' ' || c == '\t' || c == '\n' || c == 39 || c == 34)
			return (1);
	}
	else
	{
		if (c == 39 || c == 34)
			return (1);
	}
	return (0);
}

void	jump_spaces_more(char *str, t_split *split)
{
	while (str[split->i] && ft_is_space(str[split->i], split->comillas))
	{
		if (str[split->i] == 39 || str[split->i] == 34)
			split->comillas = 1;
		split->i++;
	}
	while (str[split->i] && !ft_is_space(str[split->i], split->comillas))
	{
		split->size++;
		split->i++;
	}
}

char	**create_buff(char **buff, t_split *split)
{
	if (split->comillas)
	{
		buff[split->j] = malloc(sizeof (char) * (split->size + 3));
		split->size = split->size + 2;
		split->i++;
	}
	else
		buff[split->j] = malloc(sizeof (char) * (split->size + 1));
	return (buff);
}

char	**ft_split_all(char *str, t_info *info)
{
	t_split	split;
	char	**buff;

	buff = (char **)malloc(sizeof (char *) * (info->counter + 1));
	split = start_split();
	while (str[split.i] && split.j < info->counter)
	{
		jump_spaces_more(str, &split);
		buff = create_buff(buff, &split);
		split.k = 0;
		while (split.size)
		{
			buff[split.j][split.k] = str[split.i - split.size];
			split.size--;
			split.k++;
		}
		buff[split.j][split.k] = '\0';
		split.j++;
		split.comillas = 0;
	}
	buff[split.j] = 0;
	return (buff);
}

char	**create_tokens(t_info *info)
{
	char	**str;
	int		i;

	i = 0;
	str = ft_split_all(info->input, info);
	return (str);
}
