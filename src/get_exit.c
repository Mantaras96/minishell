#include "../include/minishell.h"

extern int	g_status;

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

int get_exit(t_info *info)
{
	int ret;
	if (ft_matrix_len(info->tokens) == 2)
	{
		printf("exit");
		ret = ft_atoi(info->tokens[1]);
	}
	else if (ft_matrix_len(info->tokens) > 2)
	{
		printf("exit");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ret = 1;
	}
	else{
		printf("exit");
		ret = 0;
	}
	ret %= 256 + 256 * (ret < 0);
	return (ret);
}
