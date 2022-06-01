/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertmantaras <albertmantaras@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 00:30:13 by albertmanta       #+#    #+#             */
/*   Updated: 2022/06/01 00:53:32 by albertmanta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../ft_printf/include/ft_printf.h"
#	include "../ft_printf/include/libft.h"
#	include "../42_get_next_line/get_next_line.h"
#   include <readline/history.h>
#   include <readline/readline.h>
# 	include <limits.h>
#	include <stdio.h>

typedef struct s_minishell
{
    char    *input; //Here we will save input comand user. 
    /* data */
}               t_minishell;



typedef struct s_info
{
	char *input;
	char **tokens;
	int simples;
	int doubles;
	int counter;
	int words;



}			t_info;


int     get_pwd();
int     ft_strcmp(const char *str1, const char *str2);
void    print_star_minishell();
void    get_echo(char *str);
void	parsing(t_info *info);
void	counter(t_info *info);
int		simples(int i, t_info *info);
int		doubles(int i, t_info *info);
void	create_tokens(t_info *info);
int		create_doubles(int i, t_info *info);
int		create_simples (int i, t_info *info);
int		create_word(t_info *info, int i, char charact);
int		word_length(t_info *info, int i, char charact);