/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:34:11 by flafi             #+#    #+#             */
/*   Updated: 2023/11/28 17:13:00 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

// odd even thingy
int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	print_msg("has taken a fork", philo);
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->l_fork) != 0)
			return (pthread_mutex_unlock(philo->r_fork), 1);
		print_msg("has taken a fork", philo);
	}
	else
	{
		if (pthread_mutex_lock(philo->r_fork) != 0)
			return (pthread_mutex_unlock(philo->l_fork), 1);
		print_msg("has taken a fork", philo);
	}
	return (EXIT_SUCCESS);
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}

void	update_kill_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->time_to_kill = get_current_time() + (2 * philo->data->time_die)
		- philo->data->start_time;
	pthread_mutex_unlock(&philo->lock);
}

int	ate_all_meals(t_philo *philo)
{
	if (philo->eat_count < philo->data->num_meals)
	{
		pthread_mutex_lock(&philo->lock);
		philo->data->finished++;
		pthread_mutex_unlock(&philo->lock);
		return (0);
	}
	return (1);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	print_msg("is eating", philo);
	philo->eating = 1;
	ft_usleep(philo->data->time_eat);
	philo->eating = 0;
	pthread_mutex_lock(&philo->lock);
	philo->eat_count++;
	if (philo->eat_count == philo->data->num_meals)
		philo->data->finished += 1;
	pthread_mutex_unlock(&philo->lock);
	update_kill_time(philo);
	drop_forks(philo);
}
