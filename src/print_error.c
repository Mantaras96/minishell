/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:01:43 by amantara          #+#    #+#             */
/*   Updated: 2022/08/21 12:48:32 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

void	*print_error(int c_err, char *param, int err)
{
	if (c_err == 1)
		ft_putstr_fd("minishell: command not found: ", 2);
	else if (c_err == 2)
		ft_putstr_fd("minishell: Quotes not closed: ", 2);
	else if (c_err == 3)
		ft_putstr_fd("minishell: Is a directory: ", 2);
	else if (c_err == 4)
		ft_putstr_fd("minishell: Is not a directory: ", 2);
	else if (c_err == 5)
		ft_putstr_fd("minishell: Permission denied: ", 2);
	else if (c_err == 6)
		ft_putstr_fd("minishell: Error generating pipe: ", 2);
	else if (c_err == 7)
		ft_putstr_fd("minishell: Error getting PID program: ", 2);
	else if (c_err == 8)
		ft_putstr_fd("minishell: sintax error: ", 2);
	else if (c_err == 9)
		ft_putstr_fd("minishell: Error fork ", 2);
	else if (c_err == 10)
		ft_putstr_fd("minishell: DUP error: ", 2);
	else if (c_err == 11)
		ft_putstr_fd("minishell: export: not a valid identifier: ", 1);
	g_status = err;
	ft_putendl_fd(param, 2);
	return (NULL);
}

int	get_only_export(t_info *info)
{
	int	i;

	i = 0;
	while (info->envp[i])
	{
		printf("declare -x %s\n", info->envp[i]);
		i++;
	}
	return (0);
}

int	check_digit(char **argv)
{
	int	i;

	i = 0;
	while (argv[0][i])
	{
		if (!ft_isdigit(argv[0][i]))
		{
			free_matrix(&argv);
			return (0);
		}
		i++;
	}
	free_matrix(&argv);
	return (1);
}

char	**add_value_matrix2(char **matrix, char *newstr)
{
	char	**n_matrix;
	int		len;
	int		i;

	if (check_digit(ft_split(newstr, '=')))
	{
		print_error(11, newstr, 1);
		return (matrix);
	}
	i = 0;
	len = ft_matrix_len(matrix);
	n_matrix = malloc(sizeof(char *) * (ft_matrix_len(matrix) + 2));
	n_matrix[len + 1] = NULL;
	while (i < len)
	{
		n_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	n_matrix[i] = ft_strdup(newstr);
	free_matrix(&matrix);
	return (n_matrix);
}
