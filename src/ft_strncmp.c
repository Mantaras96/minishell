/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:49:59 by amantara          #+#    #+#             */
/*   Updated: 2022/02/04 16:12:57 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <string.h>

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*str1_copy;
	unsigned char	*str2_copy;

	if (n == 0)
		return (0);
	str1_copy = (unsigned char *)str1;
	str2_copy = (unsigned char *)str2;
	i = 0;
	while (i <= n - 1 && str1_copy[i] && str2_copy[i])
	{
		if (str1_copy[i] != str2_copy[i])
		{
			return (str1_copy[i] - str2_copy[i]);
		}
		i++;
	}
	if (i != n)
		return (str1_copy[i] - str2_copy[i]);
	return (0);
}
