#include "../include/minishell.h"

int	g_status;

void handler(int signum)
{
	if(signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
	}
	else if (signum  == SIGQUIT)
		rl_on_new_line();
	rl_on_new_line();
	rl_redisplay();
}

int signal_handler()
{
	struct termios termi;

	if (tcgetattr(STDIN_FILENO, &termi) == -1)
		return (0);
	termi.c_lflag &= ~(ECHOCTL);
	if(tcsetattr(STDIN_FILENO, TCSANOW, &termi) == -1)
		return (0);
	if(signal(SIGINT, handler))
		return (0);
	if(signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (0);
	return (1);
}

void	mini_getpid(t_info *info){
	pid_t	pid;

	pid = fork();
	if (pid < 0 || !pid)
		exit(1);
	waitpid(pid, NULL, 0);
	info->pid = pid - 1;
}

void init_info(t_info *info, char **envp)
{	
	info->doubles = 0;
	info->simples = 0;
	info->counter = 0;
	info->words = 0;
	info->redirect = 0;
	info->envp = ft_strdup_matrix(envp);
	mini_getpid(info);
}

void init_prompt(t_info *info)
{
	char *aux;
	aux = ft_strjoin("\033[1;33m", getcwd(NULL, 0));
	info->prompt = ft_strjoin(aux, "--ENCUERAO🦄🦹--->$ \033[1;00m");
}

//Info de la variable PATH: https://es.ccm.net/ordenadores/linux/2408-bash-la-variable-de-entorno-path/
void init_env(t_info *info, char **argv){
	char	*aux;

	(void)argv;
	aux = getcwd(NULL ,0);
	info->envp = set_env("PWD", aux, info->envp, 3);
	free(aux);
	aux = get_env_value("SHLVL", info->envp, 5);
	if (!aux){
		info->envp = set_env("SHLVL", "1", info->envp, 5);
		free(aux);
	}
	else
		info->envp = set_env("SHLVL", ft_itoa(ft_atoi(aux)), info->envp, 5);
	
	aux = get_env_value("PATH", info->envp, 4);
	if (!aux){
	info->envp = set_env("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", info->envp, 4);
		free(aux);
	}
	
	aux = get_env_value("_", info->envp, 1);
	if (!aux){
	 	info->envp = set_env("_", argv[0], info->envp, 1);
		free(aux);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_info *info;
	int boo;
	int n;

	n = 0;
	boo = 0;
	(void)argc;
	info = (t_info *)malloc(sizeof(t_info));
	init_info(info, envp);
	init_env(info, argv);
	print_star_minishell();
	if (signal_handler() == 0)
		return (0);
	while (42)
	{	
		init_prompt(info);
		info->input = readline(info->prompt);
		if (info->input)
		{
			add_history(info->input);
			boo = parsing(info);
			if(boo == 1){
				boo = expanding(info);
				
				info->cmds = create_nodes(info);
				check_status(info, info->cmds);
				//free_tokens(info);
			}
		} else
			exit (1);
		free(info->input);
		exit(g_status);
	}
}
