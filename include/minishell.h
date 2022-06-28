#	include "../ft_printf/include/ft_printf.h"
#	include "../ft_printf/include/libft.h"
#	include "../42_get_next_line/get_next_line.h"
#   include <readline/history.h>
#   include <readline/readline.h>
# 	include <limits.h>
#	include <stdio.h>
#   include <fcntl.h>
#	include <term.h>
#	include <termios.h>
#	include <signal.h>
#	include <dirent.h>
#	include <sys/stat.h>

typedef struct s_info
{
	char	*input;
	char	**tokens;
	int		simples;
	int		doubles;
	int		counter;
	int		words;
    int		pipe_command;
    int		redirect;
	char	**envp;
	char	*prompt;
	int		pid;
}			t_info;


int     get_pwd();
int     ft_strcmp(const char *str1, const char *str2);
void    print_star_minishell();
void    get_echo(t_info *info);
int	parsing(t_info *info);
void	counter(t_info *info);
int		simples(int i, t_info *info);
int		doubles(int i, t_info *info);
void	create_tokens(t_info *info);
int		create_doubles(int i, t_info *info);
int		create_simples (int i, t_info *info);
int		create_word(t_info *info, int i, char charact);
int		word_length(t_info *info, int i, char charact);
void init_prompt(t_info *info);
//Start (start_minishell.c)
void    start_minishell(t_info *info);
void    start_no_pipe(t_info *info);
int    check_pipe_command(t_info *info);
//Utils matrix (utils_matrix.c)
void	free_matrix(char ***matrix);
char	**add_value_matrix(char **matrix, char *newstr);
int		ft_matrix_len(char **matrix);
char	**ft_strdup_matrix(char **matrix);
char	**matrix_delete_element(char **matrix, int j);
//Get env (get_env.c)
char	**set_env(char *var, char *value, char **envp, int n);
void	get_env(t_info *info);

int		search_value_string(char *argv, int value);
char	*get_env_value(char *var, char **envp, int n);
int		count_var_envp(char *token, char **envp, int *j);
void	get_exit(t_info *info);
void	free_tokens(t_info *info);
int count_var_envp(char *token, char **envp, int *j);

//Get (export.c)
int count_var_envp(char *token, char **envp, int *j);
int get_unset(t_info *info);
int get_export(t_info *info);
int search_value_string(char *argv, int value);

int get_cd(t_info *info);
int go_home();
void update_pwd(t_info *info);
//Expanding
int		expanding (t_info *info);
char	*expand_home(char *str, int i, int quotes[2], t_info *info);
void	execute_other_commands(t_info *info);
void	get_other(t_info *info);
char 	*validate_command(char **paths, char *command);
void 	get_path(t_info *info);

