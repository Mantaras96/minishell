#include "../include/minishell.h"

/*
34 = "
39 = '
32 = ' '
*/

int word_length(t_info *info, int i, char charact)//el length de la palabra a partir del caracter si es "", ', ' '
{
	int j;

	j = 0;
	while(info->input[i + j] != charact && info->input[i + j])
		j++;
	return(j);
}

int create_word(t_info *info, int i, char charact)//creamos la palabra y la guardamos en **tokens
{
	int j;

	j = 0;
	info->tokens[info->words] = (char *)malloc(sizeof(char) * (word_length(info, i, charact) + 1));
	while (info->input[i + j] != charact && info->input[i + j])
	{
		info->tokens[info->words][j] = info->input[i + j];
		j++;
	}
	info->tokens[info->words][j] = 0;
	info->words++;
	return(word_length(info, i, charact));
}


int create_simples (int i, t_info *info)//creamos la palabra que esta entre comillas simples
{
	int j;

	j = 1;
	if (info->input[i + j] == 39)
		j++;
	else
		j += create_word(info, i + j, 39);
	return (j);
}

int create_doubles(int i, t_info *info)//creamos la palabra que esta entre comillas dobles
{
	int j;

	j = 1;
	if (info->input[i + j] == 34){
		j++;
	}
	else{
		ft_putstr_fd("Numero:", 1);
		ft_putnbr_fd(i,1);
		j += create_word(info, i + j, 34);
	}

	return (j);
}


void create_tokens(t_info *info)//aqui empieza la fumada padre, aqui basicamente guardamos las palabras, que habran a partir de nuestro contador de antes
{
	int i;

	i = 0;
	while (info->input[i])
	{
		if (info->input[i] == 32)
			i++;
		else if(info->input[i] == 34)
			i += create_doubles(i, info);
		else if(info->input[i] == 39)
			i += create_simples(i, info);
		else
			i += create_word(info, i, 32);
	}
}