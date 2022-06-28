#include "../include/minishell.h"

extern int g_status;
/* Si encontramos un pipe enviaremos un 1 se mantiene a 0 sino */ 
int check_pipe_command(t_info *info)
{
	int i;

	i = 0;
	info->pipe_command = 0;
	while (info->tokens[i])
	{
		if (info->tokens[i][0] == '|')
		{
			info->pipe_command = 1;
			return(1);
		}
		i++;
	}
	return (0);
}

void start_no_pipe(t_info *info)
{
	if (!ft_strcmp (info->tokens[0], "echo")){
		get_echo(info);
		info->simples = 0;
		info->doubles = 0;
		//free_tokens(info);
	}
	else if (!ft_strcmp (info->tokens[0], "pwd"))
		get_pwd(info);
	else if (!ft_strcmp (info->tokens[0], "exit"))
		get_exit(info);
	else if (!ft_strcmp (info->tokens[0], "env") && info->counter == 1)
		get_env(info);
	else if (!ft_strcmp (info->tokens[0], "export"))
		get_export(info);
	else if (!ft_strcmp (info->tokens[0], "unset"))
		get_unset(info);
	else if (!ft_strcmp (info->tokens[0], "cd"))
		g_status = get_cd(info);
	else if(info->tokens[0][0] == '/')
		get_path(info);
	else
		execute_other_commands(info);

}

void start_minishell(t_info *info)
{
	//Por si tenemos que inicializar variables en info.
	if(check_pipe_command(info) == 0)
		start_no_pipe(info);
}