
#include "./philosophers.h"

// check args all num and verify input values
int	ft_checkallnumvals(char **str, int argc)
{
	int	i;

	i = 1;
	if (ft_atoi(str[1]) > 200 || ft_atoi(str[1]) <= 0)
		ft_error("Input Error: Invalid number of philos");
	if (ft_atoi(str[2]) <= 0 || ft_atoi(str[3]) <= 0 || ft_atoi(str[3]) <= 0
		|| ft_atoi(str[4]) <= 0)
		ft_error("Input Error: negative or zero value");
	if (argc == 6)
		{
			if (ft_atoi(str[5]) <= 0)
				ft_error("Input Error: negative or zero num meals value");
		}
	while (str[i])
	{
		if (!ft_isalldigit(str[i]))
            ft_error("Input Error: not numeric");
		i++;
	}
	return (0);
}
// fill the program related data
void fill_progdata(t_program *progdata, char **argv, int argc)
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
void alloc_prog(t_program *progdata, t_mem_block **lst)
{
	
	// i need to free after each fail, change ft error for alloc prog as solution
	progdata->th_id = ft_malloc(lst, progdata->num_philos * sizeof(pthread_t));
	// progdata->th_id = malloc(progdata->num_philos * sizeof(pthread_t));	
	if (!progdata->th_id)
		ft_error("threads allocation failed");
	progdata->forks = malloc(progdata->num_philos * sizeof(pthread_mutex_t));
	if (!progdata->forks)
		ft_error("forks allocation failed");
	progdata->philos = malloc(progdata->num_philos * sizeof(t_philo));
	if (!progdata->philos)
		ft_error("philos allocation failed");
	pthread_mutex_init(&progdata->write, NULL);
	pthread_mutex_init(&progdata->lock, NULL);
}
int	main(int argc, char **argv)
{
	t_program progdata;
	t_mem_block *lst;

	if (argc == 5 || argc == 6)
	{
	    ft_checkallnumvals(argv, argc);
		// =start

		fill_progdata(&progdata, argv, argc);
		alloc_prog(&progdata, &lst);
		// printf("data = %i\n", data->philo_num);
		// free(data->philos);
		// free(data);
        // (void)data;
	}
	else
	{
        ft_error("Input Error: args number");
	}
	// two paths design for 5 and 4 args
	return (EXIT_SUCCESS);
}