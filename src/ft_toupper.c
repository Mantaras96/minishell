/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:49:59 by amantara          #+#    #+#             */
/*   Updated: 2022/02/04 16:13:23 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_toupper(int c)
{
	int	diferencia;

	diferencia = 32;
	if (c >= 97 && c <= 122)
	{
		c = c - diferencia;
	}
	return (c);
}
