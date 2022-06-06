#include "../include/minishell.h"

//Esta funcion se encarga de agregar valores en nuestro env. 
// Si el valor ya esta seteado hace lo que tenemos en while sino hace add_value_matrix
char **set_env(char *var, char *value, char **envp, int n)
{
    int i;
    int j;
    char *aux1;
    if (n < 0)
        n = ft_strlen(var);
    i = 0;
    aux1 = ft_strjoin(var, "=");
    aux1 = ft_strjoin(aux1, value);
    while(!ft_strchr(aux1, '=') && envp && envp[++i]){
        j = n;
        if (j < search_value_string(envp[i], '='))
            j = search_value_string(envp[i], '=');
        if (!ft_strncmp(envp[i], var, j)){
            envp[i] = aux1;
            return (envp);
        }
    }
    envp = add_value_matrix(envp, aux1);
    free(aux1);
    return (envp);
}

// Buscamos un valor en nuestro envp y devolvemos el valor del mismo.
// Si no existe devolvemos NULL.
char *get_env_value(char *var, char **envp, int n){
    int i;
    int j;

    if (n < 0)
        n = ft_strlen(var);
    i = 0;
    while(!ft_strchr(var, '=') && envp && envp[++i])
    {
        j = n;
        if (j < search_value_string(envp[i], '='))
            j = search_value_string(envp[i], '=');
        if (!ft_strncmp(envp[i], var, j)){
            return (ft_substr(envp[i], j + 1, ft_strlen(envp[i])));
        }
    }
    return (NULL);
}

void get_env(t_info *info){
    int i;

    i = 0;
    while(i < ft_matrix_len(info->envp) - 1){
        printf("%s\n", info->envp[i]);
        i++;
    }
}