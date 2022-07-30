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

int get_exit(t_info *info, int *num_exit)
{
	int ret;

	t_commands *node;
	node = info->cmds->content;
	*num_exit = !info->cmds->next;
	if (*num_exit)
		ft_putstr_fd("exit3", 2);
	if (!node->full_cmd || !node->full_cmd[1])
		return (0);
	ret = ft_atoi(info->tokens[1]);
	if (ret == -1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(node->full_cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	else if (ft_matrix_len(info->tokens) > 2)
	{
		*num_exit = 0;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	ret %= 256 + 256 * (ret < 0);
	return (ret);
}
