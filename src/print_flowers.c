#include "../include/minishell.h"

void	print_star_minishell()
{
	int fd;
	int i;    
	char *aux;

	i = 0;
	fd = open("./assets/flor.txt", O_RDONLY);
	while (i < 5)
	{
		aux = get_next_line(fd);
		ft_printf("%s", aux);
		i++;
	}
	close(fd);
}