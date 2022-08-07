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
	t_list	*cmds;
}			t_info;


typedef struct s_commands
{
	char	**full_cmd;
	char	*full_path;
	int		ifile;
	int		ofile;
}		t_commands;

typedef struct s_split
{
	int	i;
	int	j;
	int	k;
	int	comillas;
	int	size;
}	t_split;


int     get_pwd();
int     ft_strcmp(const char *str1, const char *str2);
void    print_star_minishell();
int    	get_echo(t_commands *info);
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
void handler(int signum);

//Utils matrix (utils_matrix.c)
void	free_matrix(char ***matrix);
char	**add_value_matrix(char **matrix, char *newstr);
int		ft_matrix_len(char **matrix);
char	**ft_strdup_matrix(char **matrix);
char	**matrix_delete_element(char **matrix, int j);
//Get env (get_env.c)
char	**set_env(char *var, char *value, char **envp, int n);
int	get_env(t_info *info);

int		search_value_string(char *argv, int value);
char	*get_env_value(char *var, char **envp, int n);
int		count_var_envp(char *token, char **envp, int *j);
int	get_exit(t_info *info, int *num_exit);
void	free_tokens(t_info *info);
int count_var_envp(char *token, char **envp, int *j);

//Get (export.c)
int count_var_envp(char *token, char **envp, int *j);
int	get_unset(t_info *info, char **full_cmd);
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

int is_builtin(t_commands *n);

t_list	*create_nodes(t_info *info, int i, t_list *cmd_1, t_list *cmd_2);
t_commands *command_init(void);

t_commands *get_outfile2(t_commands *node, char **temp2, int *i);
t_commands *get_outfile1(t_commands *node, char **temp2, int *i);
t_commands *get_infile2(t_commands *node, char **temp2, int *i);
t_commands *get_infile1(t_commands *node, char **temp2, int *i);

int	get_fd(int oldfd, char *path, int flags[2]);

void *validate_fork(t_info *info, t_list *cmds, int p_fd[2]);

int builtin(t_info *info, t_list *cmds, int *num_exit);
void *check_status(t_info *info, t_list *cmds);

char	**ft_cmdsubsplit(char const *s, char *set);

char	**ft_matrix_replace_in(char ***big, char **small, int n);

char	**remove_quotes(char **tokens);

void    *start_args(char *str, t_info *info);


void free_cnt(void *content);


int heredoc(char *str[2], char *aux[2]);

char *here_str(char *str[2], size_t len, char *aux_1, char * aux_2);

void	*error(int err);

void    checkInfoCdms(t_list *cmd);

t_split	start_split();

void	init_info(t_info *info, char **envp, char **argv);

int	signal_handler(void);

void	*exec_command(t_info *info, t_list *cmds);