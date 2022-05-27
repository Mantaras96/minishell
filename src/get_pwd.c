/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerida- <tmerida-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:18:08 by tmerida-          #+#    #+#             */
/*   Updated: 2022/05/27 18:18:09 by tmerida-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_strcmp(const char *str1, const char *str2)
{
    while (*str1)
    {
        if (*str1 != *str2) {
            break;
        }
        str1++;
        str2++;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

int get_pwd()
{
	char pwd[PATH_MAX];
	if (getcwd(pwd, sizeof(pwd)) != NULL)
		printf("%s\n", pwd);
	return (0);
}