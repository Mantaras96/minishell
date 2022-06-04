#include "../include/minishell.h"


void handler(int signum)
{
	if(signum == SIGINT){
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void init_info(t_info *info)
{
	info->doubles = 0;
	info->simples = 0;
	info->counter = 0;
	info->words = 0;
	info->redirect = 0;
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
	init_info(info);
	char *pwd = NULL;
	while (42)
	{
		pwd = getcwd(pwd, sizeof(pwd));
		pwd = ft_strjoin("\033[1;33m", pwd);

		info->input = readline(ft_strjoin(pwd, "--ENCUERAO🦄🦹--->$ \033[1;00m"));
		if (info->input)
		{
			parsing(info);
			start_minishell(info);

		} else
			exit (1);
		free(info->input);
	}
}
