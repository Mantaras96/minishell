#include "../include/minishell.h"

void get_echo(char *str)
{
    char **splitted;
    int i;
    //int len;

    splitted = ft_split(str, ' ');
    //len = ft_strlen(splitted);
    //printf("%d",len);
    if (!ft_strcmp(splitted[0], "echo")){
        i = 1;
        while(splitted[i]){
            printf("%s", splitted[i]);
            i++;
        }
        printf("\n");
    }
}