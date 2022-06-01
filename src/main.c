#include "../include/minishell.h"
#include <fcntl.h>

void handler(int signum)
{
	if(signum == SIGINT){
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

int main(int argc, char **argv, char **envp)
{
	t_info *info;

	(void)argc;
	(void)argv;
	(void)envp;
	print_star_minishell();
	info = (t_info *)malloc(sizeof(t_info));
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		info->doubles = 0;
		info->simples = 0;
		info->counter = 0;
		info->words = 0;
		info->input = readline("ENCUERAO🦄🦹-->$ ");
		if (info->input)
		{
			parsing(info);
			//printf("hola");
			/*if(!ft_strcmp(info->input, "pwd"))
				get_pwd();
			else if (!ft_strcmp(ft_split(info->input, ' ')[0], "echo"))
				get_echo(info->input);
				*/
		} else
			exit (1);
	}
}
