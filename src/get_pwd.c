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
	char pwd[PATH_MAX];
	if (getcwd(pwd, sizeof(pwd)) != NULL)
		printf("%s\n", pwd);
	return (0);
}