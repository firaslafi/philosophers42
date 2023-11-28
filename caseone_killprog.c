/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caseone_killprog.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:23:02 by flafi             #+#    #+#             */
/*   Updated: 2023/11/28 17:41:17 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	print_msg_adj(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write);
	printf("%ld %d %s\n", get_current_time()
		- (long)philo->data->start_time - 500, philo->id, "has died");
	pthread_mutex_unlock(&philo->data->write);
}

void	*routine_one(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	return ((void *)0);
}

int	case_one(t_program *progdata, t_mem_block **lst)
{
	progdata->start_time = get_current_time();
	if (pthread_create(&progdata->th_id[0], NULL, &routine_one,
			&progdata->philos[0]))
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

void	kill_program(t_program *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].lock);
		data->philos[i].data->dead = 1;
		pthread_mutex_unlock(&data->philos[i].lock);
	}
}
