#include "../include/minishell.h"

	// char	**full_cmd;
	// char	*full_path;
	// int		ifile;
	// int		ofile;


void    checkInfoCdms(t_list *cmd)
{
	t_commands	*c;
    int i;

    i = 0;

    while (cmd)
    {
    t_commands *c;
    c = cmd->content;
    while (c->full_cmd[i]){
        printf ("Full_cmd[%d]: %s\n", i, c->full_cmd[i]);
        i++;
    }
    printf("Full path: %s\n", c->full_path );

    printf ("IntFile: %d Outfile: %d\n", c->ifile, c->ofile);
    cmd = cmd->next;
    }
}