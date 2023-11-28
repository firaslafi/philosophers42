/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:34:53 by flafi             #+#    #+#             */
/*   Updated: 2023/11/28 17:54:42 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	*monitor(void *philo_pointer)
{
	t_philo	*philos;
	bool	all_finished;

	philos = (t_philo *)philo_pointer;
	all_finished = false;
	while (all_finished == false)
	{
		if (check_dead(philos))
		{
			ft_usleep(500);
			print_msg_adj(philos);
			all_finished = true;
		}
		pthread_mutex_lock(&philos->data->write);
		if (philos->data->finished == philos->data->num_philos)
			all_finished = true;
		pthread_mutex_unlock(&philos->data->write);
		if (all_finished == true)
		{
			ft_usleep(500);
			kill_program(philos->data);
			break ;
		}
	}
	return (NULL);
}

//  testing stuff
void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;
	long	current_time;

	philo = (t_philo *)philo_pointer;
	ft_usleep(philo->data->time_die - 10);
	while (1)
	{
		current_time = get_current_time() - (long)philo->data->start_time;
		if (check_dead(philo) == 1)
		{
			pthread_mutex_lock(&philo->data->write);
			if (philo->data->num_meals == -1)
				printf("%ld %d %s\n", current_time, philo->id, "has died");
			pthread_mutex_unlock(&philo->data->write);
			kill_program(philo->data);
			break ;
		}
		pthread_mutex_lock(&philo->lock);
		if (philo->time_to_kill == current_time)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	if (philo->id % 2 != 0)
	{
		print_msg("is thinking", philo);
		ft_usleep(philo->data->time_die / 2);
	}
	while (check_dead(philo) == 0)
	{
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
		if (pthread_create(&m_tid, NULL, &monitor, progdata->philos) != 0)
			ft_error_init("monitor thread creating failled", lst, progdata);
	}
	if (pthread_create(&progdata->philos[0].t1, NULL, &supervisor,
			&progdata->philos[0]))
		ft_error_init("supervisor thread creating failled", lst, progdata);
	i = -1;
	while (++i < progdata->num_philos)
	{
		if (pthread_create(&progdata->th_id[i], NULL, &routine,
				&progdata->philos[i]) != 0)
			ft_error_init("thread creating failled", lst, progdata);
	}
	i = -1;
	while (++i < progdata->num_philos)
		if (pthread_join(progdata->th_id[i], NULL) != 0)
			ft_error_init("thread joining failled", lst, progdata);
	pthread_join((progdata->philos[0].t1), NULL);
	pthread_join(m_tid, NULL);
}

int	main(int argc, char **argv)
{
	t_program	progdata;
	t_mem_block	*lst;

	lst = NULL;
	if (argc == 5 || argc == 6)
	{
		ft_checkallnumvals(argv, argc, &lst);
		fill_progdata(&progdata, argv, argc);
		alloc_prog(&progdata, &lst);
		init_forks(&progdata);
		init_philos(&progdata);
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
