#include "../include/minishell.h"

/*
34 = "
39 = '
32 = ' '
*/

int ft_is_space(char c, int comillas){
	if (!comillas)
	{
    if (c == ' ' || c == '\t' || c == '\n' || c == 39 || c == 34)
        return (1);
	} else {
	if (c == 39 || c == 34)
        return (1);
	}
    return (0);
}

char **ft_split_all(char *str, t_info *info){
    int i;
    int j;
    int k;
    int size;
	int comillas = 0;
    char **buff;

    buff = (char **)malloc(sizeof (char *) * (info->counter + 1));
    i = 0;
    j = 0;
    k = 0;
    size = 0;
    while (str[i] && j < info->counter){
        while (str[i]  && ft_is_space(str[i], comillas)){
			if (str[i] == 39 || str[i] == 34)
				comillas = 1;
            i++;
        }
        while (str[i] && !ft_is_space(str[i], comillas)){
            size++;
            i++;
        }
        if (comillas){
        	buff[j] = malloc(sizeof (char) * (size + 3));
        	size++;
        	size++;
        	i++;
        } else {
        	buff[j] = malloc(sizeof (char) * (size + 1));
        }

        k = 0;
        while(size){ 
            buff[j][k] = str[i - size];
            size--;
            k++;
        }
        buff[j][k] = '\0';
        j++;
		comillas = 0;
    }
    buff[j] = 0;
    //printf("PALABRAS: %d\n", j);
    return (buff);
}

//aqui empieza la fumada padre, aqui basicamente guardamos las palabras, que habran a partir de nuestro contador de antes
void create_tokens(t_info *info)
{
		char **str;
		int i;

		i = 0;
		str = ft_split_all(info->input, info);
		info->tokens = ft_strdup_matrix(str);
		//free_matrix(&str);
}