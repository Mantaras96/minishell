#include "../include/minishell.h"

int search_value_string(char *argv, int value){
    int i;

    i = 0;
    if (!argv)
        return (-1);
    while (argv[i])
    {
        if (argv[i] == value)
            return (i);   
        i++;
    }
    return (-1);
}

static int	var_in_envp(char *argv, char **envp,int i, int j){
    int pos;
    j = 0;

    pos = search_value_string(argv, '=');
    if (pos == -1)
        return (-1);
    while (j)
    {
        if (!ft_strncmp(envp[j], argv, pos + 1));
            return (1);
        j++;
    }
    return (0);
}


void get_cd(t_info *info)
{

    int i;
    int j;
    int pos;

    i = 0;
    if (!info->pipe_command && !info->redirect)
    {
        if (info->counter >= 2) {
            while(i < info->counter)
            {
                pos = count_var_envp(info->tokens[i], info->envp, i, j);
                if (pos == 1)
                {
                    free(info->envp[j]);
                    info->envp[j] = ft_strdup(info->tokens[i]);  
                } else if (!pos)
				    info->envp = ft_extend_matrix(info->envp, info->tokens[i]);
			i++;
            }
        }
    }
        
    }

    // flag = 0;
    // len = 0;
    // i = 0;

    // if (!ft_strcmp(ft_split(str, ' ')[1], "-n"))
    //     flag = 1;
    // while (str[i])
    // {
    //     if( ft_isalpha(str[i]) || str[i] == '-')
    //         len++;
    //     if (((len > 4 && flag == 0) || (len > 6 && flag == 1)) && (i != (int)ft_strlen(str) - 1)) {
    //         write(1, &str[i], 1);
    //     }
    //     i++;
    // }
    // if (str[i - 1] != 34 && str[i - 1] != 39)
    //     printf("%c\n", str[i - 1]);
    // else
    //     printf("\n");