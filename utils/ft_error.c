

#include "../philosophers.h"

void	ft_error(char *msg, t_mem_block **lst)
{
	printf("%s\n", msg);
	ft_free_all(lst);
	exit(EXIT_FAILURE);
}