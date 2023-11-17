/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:34:11 by flafi             #+#    #+#             */
/*   Updated: 2023/11/17 11:00:26 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void print_msg(t_philo *philo)
{
    u_int64_t	action_time;

    pthread_mutex_lock(&philo->data->write);
    action_time = get_time() - philo->data->start_time;
    
    pthread_mutex_unlock(&philo->data->write);
}
void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	printf("philo number %i took a right fork\n", philo->id);
	pthread_mutex_lock(philo->l_fork);
	printf("philo number %i took a left fork\n", philo->id);
}
void	drop_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	printf("philo number %i dropped a right fork\n", philo->id);
	pthread_mutex_lock(philo->l_fork);
	printf("philo number %i dropped a left fork\n", philo->id);
    ft_usleep(philo->data->time_sleep);
    printf("philo number %i is sleeping now\n", philo->id);
}
