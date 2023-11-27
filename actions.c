/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:34:11 by flafi             #+#    #+#             */
/*   Updated: 2023/11/27 20:45:00 by flafi            ###   ########.fr       */
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
int check_dead(t_philo *philo)
{
	// long	current;
	
	pthread_mutex_lock(&philo->lock);
	if (philo->data->dead == 1)
		{
			pthread_mutex_unlock(&philo->lock);
			return(1);
		}
	pthread_mutex_unlock(&philo->lock);
	return (0);
	// current = get_current_time() - philo->data->start_time;
	// if (current >= philo->time_to_kill && !philo->eating)
	// {
	// 	pthread_mutex_lock(&philo->lock);
	// 	philo->data->dead = 1;
	// 	pthread_mutex_unlock(&philo->lock);
	// 	return(1);
	// }
	// else
	// 	return (0);
}
void print_msg(char *msg, t_philo *philo)
{
    long	action_time;

    action_time = get_current_time() - philo->data->start_time;
	
    pthread_mutex_lock(&philo->data->write);
	if (!check_dead(philo))
		printf("%ld %d %s\n", action_time, philo->id, msg);
    pthread_mutex_unlock(&philo->data->write);
}
// odd even thingy
int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	// if (!check_dead(philo))
		print_msg("has taken a fork", philo);
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->l_fork) != 0)
			return (pthread_mutex_unlock(philo->r_fork), 1);
		// if (!check_dead(philo))
			print_msg("has taken a fork", philo);
	}
	else
	{
		if (pthread_mutex_lock(philo->r_fork) != 0)
			return (pthread_mutex_unlock(philo->l_fork), 1);
		// if (!check_dead(philo))
			print_msg("has taken a fork", philo);
	}
	return(EXIT_SUCCESS);
}
void	drop_forks(t_philo *philo)
{
	// if (philo->id % 2 == 0)
	// 	{
	// 		pthread_mutex_unlock(philo->r_fork);
	// 		pthread_mutex_unlock(philo->l_fork);
	// 	}
	// else
	// 	{
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
		// }

}
void update_kill_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->time_to_kill = get_current_time() + (2 * philo->data->time_die) - philo->data->start_time ;
	pthread_mutex_unlock(&philo->lock);
}
int ate_all_meals(t_philo *philo)
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
	update_kill_time(philo);
	ft_usleep(philo->data->time_eat);
	philo->eating = 0;
	pthread_mutex_lock(&philo->lock);
	philo->eat_count++;
	if (philo->eat_count == philo->data->num_meals)
		philo->data->finished += 1;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}
