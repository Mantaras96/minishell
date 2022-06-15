#include "../include/minishell.h"


void free_tokens(t_info *info)
{
	int i; 

	i = 0;
	while (info->tokens[i])
	{
		free(info->tokens[i]);
		i++;
	}
	free(info->tokens);
}

void get_exit(t_info *info)
{
	free_tokens(info);
	free(info->input);
	free(info->prompt);
	free_matrix(&info->envp);
	free(info->envp);
	free(info);
	exit(0);
}
