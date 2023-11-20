/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:34:53 by flafi             #+#    #+#             */
/*   Updated: 2023/11/20 13:25:45 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
	progdata->th_id = ft_malloc(lst, (progdata->num_philos * sizeof(pthread_t)));
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
	int i;

	i = 0;
	while (i < progdata->num_philos)
	{
		progdata->philos[i].data = progdata;
		progdata->philos[i].id = i + 1;
		progdata->philos[i].time_to_die = progdata->time_die;
		progdata->philos[i].eat_count = 0;
		progdata->philos[i].eating = 0;
		pthread_mutex_init(&progdata->philos[i].lock, NULL);
		i++;
	}
}
void	*monitor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	while (!philo->data->dead)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->finished >= philo->data->num_philos)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)EXIT_SUCCESS);
}
//  testing stuff
void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	while (!philo->data->dead)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_current_time() >= philo->time_to_die && !philo->eating)
			print_msg("died", philo);
		if (philo->eat_count == philo->data->num_meals)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished++;
			philo->eat_count++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	philo->time_to_die = philo->data->time_die + get_current_time();
	if (pthread_create(&philo->t1, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	while (!philo->data->dead)
	{
		eat(philo);
		print_msg("is thinking", philo);
	}
	if (pthread_join(philo->t1, NULL))
		return ((void *)1);
	return ((void *)0);
}
// void* monitor(void* arg) {
//     // Dummy thread function
// 	(void)arg;
//     return NULL;
// }
// void* routine(void* arg) {

// 	(void)arg;

//     return NULL;
// }
void	init_threads(t_program *progdata, t_mem_block **lst)
{
	int			i;
	pthread_t	m_tid;

	progdata->start_time = get_current_time();
	if (progdata->num_meals != -1)
	{
		if (pthread_create(&m_tid, NULL, &monitor, &progdata->philos[0]) != 0)
			ft_error_init("monitor thread creating failled", lst, progdata);
	}
	i = 0;
	while (i < progdata->num_philos)
	{
		if (pthread_create(&progdata->th_id[i], NULL, &routine, &progdata->philos[i]) != 0)
			ft_error_init("thread creating failled", lst, progdata);
		ft_usleep(1);
		i++;
	}
	i = 0;
	while (i < progdata->num_philos)
	{
		if (pthread_join(progdata->th_id[i], NULL) != 0)
			ft_error_init("thread joining failled", lst, progdata);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_program progdata;
	t_mem_block *lst = NULL;

	if (argc == 5 || argc == 6)
	{
		ft_checkallnumvals(argv, argc, &lst);
		// =start
		// on exit destroy mutexs crucial shit
		fill_progdata(&progdata, argv, argc);
		alloc_prog(&progdata, &lst);
		init_forks(&progdata);
		init_philos(&progdata);

		// use ft_error_init from now on
		init_threads(&progdata, &lst);
		ft_exit(&progdata);
		ft_free_all(&lst);
	}
	else
	{
		ft_error("Input Error: args number", &lst);
	}
	// two paths design for 5 and 4 args
	return (EXIT_SUCCESS);
}
