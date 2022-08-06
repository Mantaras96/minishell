/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerida- <tmerida-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:10:23 by tmerida-          #+#    #+#             */
/*   Updated: 2022/08/06 15:18:46 by tmerida-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_info_cmds(t_list *cmd)
{
	int			i;

	i = 0;
	while (cmd)
	{	
		t_commands	*c;
		c = cmd->content;
		while (c->full_cmd[i])
		{
			printf("Full_cmd[%d]: %s\n", i, c->full_cmd[i]);
			i++;
		}
		printf("Full path: %s", c->full_path);
		printf("IntFile: %d Outfile: %d\n", c->ifile, c->ofile);
		cmd = cmd->next;
	}
}
