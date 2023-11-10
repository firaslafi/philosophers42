
#include "./philosophers.h"

// check args all num and verify input values
int	ft_checkallnumvals(char **str, int argc, t_mem_block **lst)
{
	int	i;

	i = 1;
	if (ft_atoi(str[1]) > 200 || ft_atoi(str[1]) <= 0)
		ft_error("Input Error: Invalid number of philos", lst);
	if (ft_atoi(str[2]) <= 0 || ft_atoi(str[3]) <= 0 || ft_atoi(str[3]) <= 0
		|| ft_atoi(str[4]) <= 0)
		ft_error("Input Error: negative or zero value", lst);
	if (argc == 6)
	{
		if (ft_atoi(str[5]) <= 0)
			ft_error("Input Error: negative or zero num meals value", lst);
	}
	while (str[i])
	{
		if (!ft_isalldigit(str[i]))
			ft_error("Input Error: not numeric", lst);
		i++;
	}
	return (0);
}
// fill the program related data
void	fill_progdata(t_program *progdata, char **argv, int argc)
{
	progdata->num_philos = ft_atoi(argv[1]);
	progdata->time_die = ft_atoi(argv[2]);
	progdata->time_eat = ft_atoi(argv[3]);
	progdata->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		progdata->num_meals = ft_atoi(argv[5]);
	else
		progdata->num_meals = -1;
	progdata->dead = 0;
	progdata->finished = 0;
}
void	alloc_prog(t_program *progdata, t_mem_block **lst)
{
	progdata->th_id = ft_malloc(lst, progdata->num_philos * sizeof(pthread_t));
	if (!progdata->th_id)
		ft_error("threads allocation failed", lst);
	progdata->forks = ft_malloc(lst, progdata->num_philos
			* sizeof(pthread_mutex_t));
	if (!progdata->forks)
		ft_error("forks allocation failed", lst);
	progdata->philos = ft_malloc(lst, progdata->num_philos * sizeof(t_philo));
	if (!progdata->philos)
		ft_error("philos allocation failed", lst);
	pthread_mutex_init(&progdata->write, NULL);
	pthread_mutex_init(&progdata->lock, NULL);
}
void init_forks(t_program *progdata)
{
	int i;
	
	i = 0;
	while (i < progdata->num_philos)
	{
		pthread_mutex_init(&progdata->forks[i], NULL);
		i++;
	}
	progdata->philos[0].l_fork = &progdata->forks[0];
	progdata->philos[0].r_fork = &progdata->forks[progdata->num_philos - 1];
	i = 1;
	while (i < progdata->num_philos)
	{
		progdata->philos[i].l_fork = &progdata->forks[i];
		progdata->philos[i].r_fork = &progdata->forks[i - 1];
		i++;
	}

}
void init_philos(t_program *progdata)
{
	
}

int	main(int argc, char **argv)
{
	t_program progdata;
	t_mem_block *lst;

	if (argc == 5 || argc == 6)
	{
		ft_checkallnumvals(argv, argc, &lst);
		// =start

		fill_progdata(&progdata, argv, argc);
		alloc_prog(&progdata, &lst);
		init_forks(&progdata);
		ft_free_all(&lst);
	}
	else
	{
		ft_error("Input Error: args number", &lst);
	}
	// two paths design for 5 and 4 args
	return (EXIT_SUCCESS);
}