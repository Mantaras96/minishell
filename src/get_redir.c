
#include "../include/minishell.h"

extern int	g_status;

int	get_fd(int oldfd, char *path, int i, int j)
{
    int fd;

    if (oldfd > 2)
        close(oldfd);
    if (!path)
        return(-1);
	if (access(path, F_OK) == -1 && !i)
		write(1, "Error", 5);
	else if (!i && access(path, R_OK) == -1)
		write(1, "Error", 5);
	else if (i && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		write(1, "Error", 5);
	if (i && j)
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (i && !j)
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!i && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
    
}

t_commands *get_outfile2(t_commands *node, char **temp2, int *i){
    int j;
    int x;

    j = 1;
    x = 1;
    (*i)++;
    if (temp2[++(*i)])
        node->ofile = get_fd(node->ofile, temp2[*i], j, x);
    if (!temp2[*i] || node->ofile == -1)
    {
        *i = -1;
        if (node->ofile != -1){
            ft_putendl_fd("Error", 2);
            g_status = 2;
        }
        else
            g_status = 1;
    }
    return (node);
}

t_commands *get_outfile1(t_commands *node, char **temp2, int *i){
    int j;
    int x;

    j = 1;
    x = 0;
    (*i)++;
    if (temp2[*i])
        node->ofile = get_fd(node->ofile, temp2[*i], j, x);
    if (!temp2[*i] || node->ofile == -1)
    {
        *i = -1;
        if (node->ofile != -1){
            ft_putendl_fd("Error", 2);
            g_status = 2;
        }
        else
            g_status = 1;
    }
    return (node);
}

t_commands *get_infile2(t_commands *node, char **temp2, int *i){
    char	*aux[2];
	char	*nl;
	char	*str[2];

	str[0] = NULL;
	str[1] = NULL;
	aux[0] = NULL;
	aux[1] = "end-of-file";
    (*i)++;
	if (temp2[++(*i)])
	{
		aux[0] = temp2[*i];
		node->ifile = heredoc(str, aux);
	}
    if (!temp2[*i] || node->ifile == -1)
    {
        *i = -1;
        if (node->ifile != -1){
            ft_putendl_fd("Error", 2);
            g_status = 2;
        }
        else
            g_status = 1;
    }
    return (node);
}

t_commands *get_infile1(t_commands *node, char **temp2, int *i){
    int j;
    int x;

    j = 0;
    x = 0;
    (*i)++;
    if (temp2[*i])
        node->ifile = get_fd(node->ifile, temp2[*i], j, x);
    if (!temp2[*i] || node->ifile == -1)
    {
        *i = -1;
        if (node->ifile != -1){
            ft_putendl_fd("Error", 2);
            g_status = 2;
        }
        else
            g_status = 1;
    }
    return (node);
}
