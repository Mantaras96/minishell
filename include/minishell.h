/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 00:30:13 by albertmanta       #+#    #+#             */
/*   Updated: 2022/05/27 19:24:51 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../ft_printf/include/ft_printf.h"
#	include "../ft_printf/include/libft.h"
#	include "../42_get_next_line/get_next_line.h"
#   include <readline/history.h>
#   include <readline/readline.h>
# 	include <limits.h>
#	include <stdio.h>


int     get_pwd();
int     ft_strcmp(const char *str1, const char *str2);
void    print_star_minishell();
void    get_echo(char *str);