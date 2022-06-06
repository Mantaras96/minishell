#	include "../ft_printf/include/ft_printf.h"
#	include "../ft_printf/include/libft.h"
#	include "../42_get_next_line/get_next_line.h"
#   include <readline/history.h>
#   include <readline/readline.h>
# 	include <limits.h>
#	include <stdio.h>
#   include <fcntl.h>
#	include <term.h>

typedef struct s_minishell
{
    char    *input; //Here we will save input comand user. 
    /* data */
}               t_minishell;



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
}			t_info;


int     get_pwd();
int     ft_strcmp(const char *str1, const char *str2);
void    print_star_minishell();
void    get_echo(t_info *info);
void	parsing(t_info *info);
void	counter(t_info *info);
int		simples(int i, t_info *info);
int		doubles(int i, t_info *info);
void	create_tokens(t_info *info);
int		create_doubles(int i, t_info *info);
int		create_simples (int i, t_info *info);
int		create_word(t_info *info, int i, char charact);
int		word_length(t_info *info, int i, char charact);
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

int		search_value_string(char *argv, int value);
char	*get_env_value(char *var, char **envp, int n);
int count_var_envp(char *token, char **envp, int *j);