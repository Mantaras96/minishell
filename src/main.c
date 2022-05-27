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
	char *input;

	(void)argc;
	(void)argv;
	(void)envp;
	print_star_minishell();
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		input = readline("ENCUERAO🦄🦹-->$ ");
		if (input)
		{
			if(!ft_strcmp(input, "pwd"))
				get_pwd();
		}else
			exit (1);
	}
}