#include "../include/minishell.h"

int search_value_string(char *argv, int value){
    int i;

    i = 0;
    if (!argv)
        return (-1);
    while (argv[i])
    {
        if (argv[i] == (unsigned char)value)
            return (i);   
        i++;
    }
    if ((unsigned char)value == '\0')
		return (i);
    return (-1);
}

//Agregar valor a la matrix de info envp.
// Si pos existe modificamos el valor mientras que si no existe creamos una nueva en la matrix.
int get_export(t_info *info){

    int i;
    int j;
    int pos;

    i = 0;
    j = 0;
    if (!info->pipe_command && !info->redirect)
    {
        if (info->counter >= 2) {
            while(i < info->counter)
            {
                pos = count_var_envp(info->tokens[i], info->envp, &j);
                if (pos == 1)
                {
                    free(info->envp[j]);
                    info->envp[j] = ft_strdup(info->tokens[i]);  
                } else if (!pos){
				    info->envp = add_value_matrix(info->envp, info->tokens[i]);
                }
			i++;
            }
        }
    }
    return (0);
}

int count_var_envp(char *token, char **envp, int *j)
{
    int aux;
    int i;

    i = 0;
    aux = search_value_string(token, '=');
    if (!aux)
        return (-1);
    while(i < ft_matrix_len(envp) - 1){;
        if (!ft_strncmp(envp[i], token, aux + 1))
            return (1);
        i++;
        *j = i;
    }
    return (0);
}

//Eliminar un  valor de la matrix de info envp.
int get_unset(t_info *info){

    int i;
    int j;
    int pos;

    i = 1;
    j = 0;
    if (!info->pipe_command && !info->redirect)
    {
        if (info->counter >= 2) {
            while (info->tokens[i]){
            pos =  count_var_envp(info->tokens[i], info->envp, &j);
            printf("\nPosicion:%d, %d \n", j, pos);

            if (!pos)
                return (0);
            else 
                //info->envp = matrix_delete_element(info->envp, j);
            i++;
            }

        }
    }
    return (0);
}