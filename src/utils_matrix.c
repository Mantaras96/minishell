#include "../include/minishell.h"

void free_matrix(char ***matrix){
	int i;

	i = 0;
	while(matrix && matrix[0] && matrix[0][i])
	{
		free(matrix[0][i]);
		i++;
	}
	if (matrix)
	{
		free(matrix[0]);
		*matrix = NULL;
	}
}


char **add_value_matrix(char **matrix, char *newstr){
	char **n_matrix;
	int len;
	int i;

	i = 0;
	len = ft_matrix_len(matrix);
	n_matrix = malloc(sizeof(char *) * (ft_matrix_len(matrix) + 2));
	while (i < len)
	{
		n_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	n_matrix[++i] = ft_strdup(newstr);
	n_matrix[i] = NULL;
	free_matrix(&matrix);
	return (n_matrix);
}

int ft_matrix_len(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i])
		i++;
	return (i);
}


char	**ft_strdup_matrix(char **matrix)
{
	char **m_return;
	int i;
	int size;

	size = ft_matrix_len(matrix);
	m_return = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (m_return[i]){
		m_return[i] = ft_strdup(matrix[i]);
		i++;
	}
	m_return[i] = NULL;
	return (m_return);
}

char **matrix_delete_element(char **matrix, int j){
	char **m_return;
	int i;
	int x;
	int size;

	size = ft_matrix_len(matrix);
	m_return = malloc(sizeof(char *) * (size));
	i = 0;
	x = 0;
	while (m_return[++i]){
		if (i == j)
		{
			continue;
		}
		m_return[x++] = ft_strdup(matrix[i]);
	}
	m_return[x] = NULL;
	free_matrix(&matrix);
	return (m_return);
}
