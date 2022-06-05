#include "../include/minishell.h"


void handler(int signum)
{
	if(signum == SIGINT){
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void init_info(t_info *info, char **envp)
{
	info->doubles = 0;
	info->simples = 0;
	info->counter = 0;
	info->words = 0;
	info->redirect = 0;
	info->envp = ft_strdup_matrix(envp);
}

//Info de la variable PATH: https://es.ccm.net/ordenadores/linux/2408-bash-la-variable-de-entorno-path/
void init_env(t_info *info, char **argv){
	char *aux;

	(void)argv;
	aux = getcwd(NULL ,0);
	info->envp = set_env("PWD", aux, info->envp, 3);
	aux = get_env_value("SHLVL", info->envp, 5);
	if (!aux)
		info->envp = set_env("SHLVL", "1", info->envp, 5);
	else
		info->envp = set_env("SHLVL", ft_itoa(ft_atoi(aux)), info->envp, 5);

	// aux = get_env_value("PATH", info->envp, 4);
	// if (!aux){
	// 	info->envp = set_env("PATH", "/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", info->envp, 4);
	// }

	// aux = get_env_value("_", info->envp, 1);
	// if (!aux)
	// 	info->envp = set_env("_", argv[0], info->envp, 1);
		write (1, "Y", 1);
}

int main(int argc, char **argv, char **envp)
{
	t_info *info;

	(void)argc;
	info = (t_info *)malloc(sizeof(t_info));
	init_info(info, envp);
	init_env(info, argv);
	print_star_minishell();

	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);

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
