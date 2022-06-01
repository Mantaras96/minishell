#include "../include/minishell.h"

/* Si encontramos un pipe enviaremos un 1 se mantiene a 0 sino */ 
void check_pipe_command(t_info *info)
{
	int i;

	i = 0;
	while (info->tokens[i][0])
	{
		if (info->tokens[i][0] == '|')
		{
			info->pipe_command = 1;
			break;
		}
		i++;
	}
}

void start_no_pipe(t_info *info)
{

	if (!ft_strcmp (info->tokens[0], "echo"))
		get_echo(info);
	else if (ft_strcmp (info->tokens[0], "pwd"))
		get_pwd(info);
	// else if (ft_strcmp (info->tokens[0], "env"))
	// else if (ft_strcmp (info->tokens[0], "export"))
	// else if (ft_strcmp (info->tokens[0], "unset"))
	// else if (ft_strcmp (info->tokens[0], "exit"))
}

void start_minishell(t_info *info)
{
	//Por si tenemos que inicializar variables en info.
	info->pipe_command = 0;
	check_pipe_command(info);

	if(!info->pipe_command)
		start_no_pipe(info);
}