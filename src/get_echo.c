#include "../include/minishell.h"

void get_echo(char *str)
{
    int i;
    int len;
    int flag;

    flag = 0;
    len = 0;
    i = 0;


    if (!ft_strcmp(ft_split(str, ' ')[1], "-n"))
        flag = 1;
    while (str[i])
    {
        if( ft_isalpha(str[i]) || str[i] == '-')
            len++;
        if (((len > 4 && flag == 0) || (len > 6 && flag == 1)) && (i != (int)ft_strlen(str) - 1)) {
            write(1, &str[i], 1);
        }
        i++;
    }
    if (str[i - 1] != 34 && str[i - 1] != 39)
        printf("%c\n", str[i - 1]);
    else
        printf("\n");

}