/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:34:11 by flafi             #+#    #+#             */
/*   Updated: 2023/11/19 11:58:46 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void print_msg(char *msg, t_philo *philo)
{
    u_int64_t	action_time;

    pthread_mutex_lock(&philo->data->write);
    action_time = get_current_time() - philo->data->start_time;
	if (ft_strcmp("died", msg) == 0 && philo->data->dead == 0)
	{
		printf("%llu %d %s\n", action_time, philo->id, msg);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%llu %d %s\n", action_time, philo->id, msg);
    pthread_mutex_unlock(&philo->data->write);
}
void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_msg("has taken a fork", philo);
	pthread_mutex_lock(philo->l_fork);
	print_msg("has taken a fork", philo);
}
void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	print_msg("is sleeping", philo);
    ft_usleep(philo->data->time_sleep);
}
void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = get_current_time() + philo->data->time_die;
	print_msg("is eating", philo);
	philo->eat_count++;
	ft_usleep(philo->data->time_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}
