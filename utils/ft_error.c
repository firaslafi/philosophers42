

#include "../philosophers.h"

void	ft_exit(t_program *progdata)
{
	int	i;

	i = 0;
	while (i < progdata->num_philos)
	{
		pthread_mutex_destroy(&progdata->forks[i]);
		pthread_mutex_destroy(&progdata->philos[i].lock);
		i++;
	}
	pthread_mutex_destroy(&progdata->write);
	pthread_mutex_destroy(&progdata->lock);
}

void	ft_error(char *msg, t_mem_block **lst)
{
	printf("%s\n", msg);
	ft_free_all(lst);
	exit(EXIT_FAILURE);
}
void	ft_error_init(char *msg, t_mem_block **lst, t_program *progdata)
{
	printf("%s\n", msg);
	ft_free_all(lst);
	if (progdata)
		ft_exit(progdata);
	exit(EXIT_FAILURE);
}