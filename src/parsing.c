#include "../include/minishell.h"

/*
34 = "
39 = '
32 = ' '
*/

int doubles(int i, t_info *info) //fumas porros tio
{
	info->doubles--;
	if (info->input[i] == 34)
		i++;
	else if (info->doubles != 0)
	{
		info->counter++;
		while (info->input[i] && info->input[i] != 34)
		{
			if (info->input[i] == 39)
				info->simples--;
			i++;
		}
	}
	return (i + 1);
}

int simples(int i, t_info *info)//mejor si te lo dibujas bro
{
	info->simples--;
	if (info->input[i] == 39)
		i++;
	else if (info->simples != 0)
	{
		info->counter++;
		while (info->input[i] && info->input[i] != 39)
		{
			if (info->input[i] == 34)
				info->doubles--;
			i++;
		}
	}
	return (i + 1);
}

void counter(t_info *info)//Vamos recorriendo si hay una comilla doble o simple, hasta que se cierre sera una palabra, sino hay comillas, el counter++ de una palabra
{
	int i;

	i = 0;
	while (info->input[i])
	{
		if (info->input[i] == 32)
			i++;
		else if(info->input[i] == 34)
			i = doubles(i + 1, info);
		else if(info->input[i] == 39)
			i = simples(i + 1, info);
		else
		{
			info->counter++;
			while (info->input[i] && info->input[i] != 32)
				i++;
		}
	}
}

void parsing(t_info *info) //recorremos hasta el final, contamos las comilla simples, y las dobles.
{
	int i;
	i = 0;
	while (info->input[i])
	{
		if (info->input[i] == 34)
			info->doubles++;
		else if (info->input[i] == 39)
			info->simples++;
		i++;
	}
	counter(info);
	info->tokens = (char **)malloc(sizeof(char *) * (info->counter + 1));
	info->tokens[info->counter] = 0;
	create_tokens(info);

	i = 0; 
	printf("%d\n", info->counter);
	while (info->tokens[i])
	{
		printf("%s\n", info->tokens[i]);
		i++;
	}
}