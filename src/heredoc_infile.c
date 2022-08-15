/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_infile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:34:19 by amantara          #+#    #+#             */
/*   Updated: 2022/08/15 13:11:50 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*here_str(char *str[2], size_t len, char *aux_1, char *aux_2)
{
	char	*temp;

	while (g_status != 130 && (!str[0] || ft_strncmp(str[0], aux_1, len) \
		|| ft_strlen(aux_1) != len))
	{
		temp = str[1];
		str[1] = ft_strjoin(str[1], str[0]);
		free(temp);
		free(str[0]);
		str[0] = readline("> ");
		if (!str[0])
		{
			printf("%s (wanted `%s\')\n", aux_2, aux_1);
			break ;
		}
		temp = str[0];
		str[0] = ft_strjoin(str[0], "\n");
		free(temp);
		len = ft_strlen(str[0]) - 1;
	}
	free(str[0]);
	return (str[1]);
}

int	heredoc(char *str[2], char *aux[2])
{
	int	fd[2];

	g_status = 0;
	if (pipe(fd) == -1)
	{
		error(1);
		return (-1);
	}
	str[1] = here_str(str, 0, aux[0], aux[1]);
	if (str[1])
		write(fd[1], str[1], ft_strlen(str[1]));
	free (str[1]);
	close (fd[1]);
	if (g_status == 130)
	{
		close (fd[0]);
		return (-1);
	}
	return (fd[0]);
}
