#include "../include/minishell.h"

int ft_strcmp(const char *str1, const char *str2)
{
    if(!str1)
        return(1);
    while (*str1)
    {
        if (*str1 != *str2) {
            break;
        }
        str1++;
        str2++;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

int get_pwd()
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}