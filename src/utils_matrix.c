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
	n_matrix[len + 1] = NULL;
	while (i < len)
	{
		n_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	n_matrix[i] = ft_strdup(newstr);
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
	//printf("MATRIX: %d\n",  size);
	m_return = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (matrix[i]){
		m_return[i] = ft_strdup(matrix[i]);
		i++;
	}
	m_return[i] = NULL;
	//free_matrix(&matrix);
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

char	**ft_matrix_replace_in(char ***big, char **small, int n)
{
	char	**aux;
	int		i[3];

	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	if (!big || !*big || n < 0 || n >= ft_matrix_len(*big))
		return (NULL);
	aux = ft_calloc(ft_matrix_len(*big) + ft_matrix_len(small), sizeof(char *));
	while (aux && big[0][++i[0]])
	{
		if (i[0] != n)
			aux[++i[2]] = ft_strdup(big[0][i[0]]);
		else
		{
			while (small && small[++i[1]])
				aux[++i[2]] = ft_strdup(small[i[1]]);
		}
	}
	free_matrix(big);
	*big = aux;
	return (*big);
}
