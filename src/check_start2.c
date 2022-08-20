/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_start2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amantara <amantara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:19:43 by tmerida-          #+#    #+#             */
/*   Updated: 2022/08/20 12:13:06 by amantara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	is_builtin(t_commands *n)
{
	if (!n->full_cmd)
		return (0);
	if ((n->full_cmd && ft_strchr(*n->full_cmd, '/')) || (n->full_path && \
		ft_strchr(n->full_path, '/')))
		return (0);
	if (!ft_strcmp(*n->full_cmd, "pwd"))
		return (1);
	if (!ft_strcmp(*n->full_cmd, "cd"))
		return (1);
	if (!ft_strcmp(*n->full_cmd, "export"))
		return (1);
	if (!ft_strcmp(*n->full_cmd, "unset"))
		return (1);
	if (!ft_strcmp(*n->full_cmd, "exit"))
		return (1);
	if (!ft_strcmp(*n->full_cmd, "echo"))
		return (1);
	if (!ft_strcmp(*n->full_cmd, "env"))
		return (1);
	return (0);
}

char	*find_cmd(char **path, char *cmd, char *full_path)
{
	char	*aux;
	int		i;

	i = -1;
	full_path = NULL;
	while (path && path[++i])
	{
		free(full_path);
		aux = ft_strjoin(path[i], "/");
		if (!aux)
			return (NULL);
		full_path = ft_strjoin(aux, cmd);
		free(aux);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break ;
	}
	if (!path || !path[i])
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

DIR	*get_dir(t_info *info, t_list *cmds, char ***s, char *path)
{
	t_commands	*c;
	DIR			*dir;

	c = cmds->content;
	dir = NULL;
	if (c && c->full_cmd)
		dir = opendir(*c->full_cmd);
	if (c && c->full_cmd && ft_strchr(*c->full_cmd, '/') && !dir)
	{
		*s = ft_split(*c->full_cmd, '/');
		c->full_path = ft_strdup(*c->full_cmd);
		free(c->full_cmd[0]);
		c->full_cmd[0] = ft_strdup(s[0][ft_matrix_len(*s) - 1]);
	}
	else if (!is_builtin(c) && c && c->full_cmd && !dir)
	{
		path = get_env_value("PATH", info->envp, 4);
		*s = ft_split(path, ':');
		free(path);
		c->full_path = find_cmd(*s, *c->full_cmd, c->full_path);
		if (!c->full_path || !c->full_cmd[0] || !c->full_cmd[0][0]){
			print_error(1, *c->full_cmd, 127);
		}
	}
	return (dir);
}

void	get_command(t_info *info, t_list *cmds, char **s, char *path)
{
	t_commands	*c;
	DIR			*dir;

	c = cmds->content;
	dir = get_dir(info, cmds, &s, path);
	if (!is_builtin(c) && c && c->full_cmd && dir)
		print_error(1, *c->full_cmd, 126); // Es un directorio
	else if (!is_builtin(c) && c && c->full_path
		&& access(c->full_path, F_OK) == -1)
		print_error(1, c->full_path, 127); // No es un directorio
	else if (!is_builtin(c) && c && c->full_path
		&& access(c->full_path, X_OK) == -1)
		print_error(1, c->full_path, 126); // No tiene permisos.
	if (dir)
		closedir(dir);
	free_matrix(&s);
	//free(path);
}

void	*exec_command(t_info *info, t_list *cmds)
{
	int	p_fd[2];

	get_command(info, cmds, NULL, NULL);
	if (pipe(p_fd) == -1)
		write(1, "pError", 6);
	if (!validate_fork(info, cmds, p_fd))
		return (NULL);
	close(p_fd[1]);
	if (cmds->next && !((t_commands *)cmds->next->content)->ifile)
		((t_commands *)cmds->next->content)->ifile = p_fd[0];
	else
		close(p_fd[0]);
	if (((t_commands *)cmds->content)->ifile > 2)
		close (((t_commands *)cmds->content)->ifile);
	if (((t_commands *)cmds->content)->ofile > 2)
		close (((t_commands *)cmds->content)->ofile);
	return (NULL);
}
