/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:34:53 by flafi             #+#    #+#             */
/*   Updated: 2023/11/25 18:54:41 by flafi            ###   ########.fr       */
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
	if (ft_atoi(str[2]) <= 0 || ft_atoi(str[3]) <= 0 || ft_atoi(str[4]) <= 0)
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
		progdata->philos[i].r_fork = &progdata->forks[(i + 1) % progdata->num_philos];
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
		progdata->philos[i].time_to_kill = progdata->time_die;
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
		if (philo->eat_count == philo->data->num_meals) {
            philo->data->finished++;
        }
		if (philo->data->finished == philo->data->num_philos)
		{
			pthread_mutex_lock(&philo->lock);
			kill_program(philo->data);
			philo->data->dead = 1;
			printf("hxxxxxxxxxxx\n");
			pthread_mutex_unlock(&philo->lock);
		}
	}
	return ((void *)EXIT_SUCCESS);
}
//  testing stuff
void *supervisor(void *philo_pointer)
{
    t_philo *philo = (t_philo *)philo_pointer;
	
	long current_time;

	if(philo->data->num_philos % 2 == 0)
		ft_usleep(philo->data->time_die / 2);
    while (1)
	{
		current_time = get_current_time() - (long)philo->data->start_time;
		if (check_dead(philo) == 1)
		{
			pthread_mutex_lock(&philo->data->write);
			printf("%ld %d %s\n", current_time, philo->id, "has died");
			pthread_mutex_unlock(&philo->data->write);
			kill_program(philo->data);
			break ;
		}
			pthread_mutex_lock(&philo->lock);
		if ((philo->time_to_kill == current_time) && philo->eating == 0)
		{
			philo->data->dead = 1;
			// break ;
		}
			pthread_mutex_unlock(&philo->lock);
    }
    return NULL;
}

void kill_program(t_program *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].lock);
		data->philos[i].data->dead = 1;
		pthread_mutex_unlock(&data->philos[i].lock);
	}
	
	// exit(EXIT_FAILURE);
	
	// join
	// i = 0;
	// while (i < data->num_philos)
	// 	pthread_join((data->philos[i].t1), NULL);
	// // pthread_join(*(data->th_id), NULL);
	// pthread_join(data->th_sup, NULL);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	while (check_dead(philo) == 0)
	{
		// testing
						pthread_mutex_lock(&philo->data->write);
						printf("time to kill philo %i = %ld\n", philo->id, philo->time_to_kill);
						pthread_mutex_unlock(&philo->data->write);
		// testing
		eat(philo);
		print_msg("is sleeping", philo);
   		ft_usleep(philo->data->time_sleep);
		print_msg("is thinking", philo);
	}

	return ((void *)0);
}

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

	if (pthread_create(&progdata->philos[0].t1, NULL, &supervisor, &progdata->philos[0]))
			ft_error_init("supervisor thread creating failled", lst, progdata);
	i = 0;
	while (i < progdata->num_philos)
	{
		if (pthread_create(&progdata->th_id[i], NULL, &routine, &progdata->philos[i]) != 0)
			ft_error_init("thread creating failled", lst, progdata);
		i++;
	}
	i = 0;
	while (i < progdata->num_philos)
	{
		if (pthread_join(progdata->th_id[i], NULL) != 0)
			ft_error_init("thread joining failled", lst, progdata);
		i++;
	}
	pthread_join((progdata->philos[0].t1), NULL);
	pthread_join(m_tid, NULL);
}
void	*routine_one(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	return ((void *)0);
}
int	case_one(t_program *progdata, t_mem_block **lst)
{
	progdata->start_time = get_current_time();
	if (pthread_create(&progdata->th_id[0], NULL, &routine_one, &progdata->philos[0]))
		ft_error_init("thread joining failled", lst, progdata);
	if (pthread_join(progdata->th_id[0], NULL) != 0)
			ft_error_init("thread joining failled", lst, progdata);
	print_msg("has taken fork", &progdata->philos[0]);
	ft_usleep(progdata->time_sleep);
	print_msg("died", &progdata->philos[0]);
	progdata->philos[0].data->dead = 1;
	ft_exit(progdata);
	ft_free_all(lst);
	return (0);
}

int	main(int argc, char **argv)
{
	t_program progdata;
	t_mem_block *lst;

	lst = NULL;
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
		if (progdata.num_philos == 1)
			case_one(&progdata, &lst);
		init_threads(&progdata, &lst);
		ft_exit(&progdata);
		ft_free_all(&lst);
	}
	else
	{
		ft_error("Input Error: args number", &lst);
	}
	return (EXIT_SUCCESS);
}
