#include "../include/minishell.h"

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