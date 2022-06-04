#include "../include/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*s3;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	s3 = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	while (s1[i] != 0)
	{
		s3[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != 0)
	{
		s3[j++] = s2[i];
		i++;
	}
	s3[j] = 0;
	return (s3);
}