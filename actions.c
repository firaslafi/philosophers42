/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:34:11 by flafi             #+#    #+#             */
/*   Updated: 2023/11/24 19:23:08 by flafi            ###   ########.fr       */
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
	u_int64_t	current;
	
		pthread_mutex_lock(&philo->lock);
		if (philo->data->dead == 1)
			{
				pthread_mutex_unlock(&philo->lock);
				return(1);
			}

		pthread_mutex_unlock(&philo->lock);
	current = get_current_time() - philo->data->start_time;
	if (current >= philo->time_to_kill && !philo->eating)
	{
		pthread_mutex_lock(&philo->lock);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->lock);
		return(1);
	}
	else
		return (0);
}
void print_msg(char *msg, t_philo *philo)
{
    u_int64_t	action_time;

    action_time = get_current_time() - philo->data->start_time;
	
    pthread_mutex_lock(&philo->data->write);
	// if (check_dead(philo))
	// {
	// 	// philo->data->dead = 1;
	// 	printf("%llu %d %s\n", action_time, philo->id, "died");
	// }
	if (philo->data->dead != 1)
		printf("%llu %d %s\n", action_time, philo->id, msg);
    pthread_mutex_unlock(&philo->data->write);
}
// odd even thingy
int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	if (!check_dead(philo))
		print_msg("has taken a fork", philo);
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->l_fork) != 0)
			return (pthread_mutex_unlock(philo->r_fork), 1);
		if (!check_dead(philo))
			print_msg("has taken a fork", philo);
	}
	else
	{
		if (pthread_mutex_lock(philo->r_fork) != 0)
			return (pthread_mutex_unlock(philo->l_fork), 1);
		if (!check_dead(philo))
			print_msg("has taken a fork", philo);
		// else
		// 	print_msg("died", philo);
	}
	return(EXIT_SUCCESS);
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
	print_msg("is sleeping", philo);
    ft_usleep(philo->data->time_sleep);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	if (check_dead(philo))
		return ;
	philo->time_to_kill = get_current_time() + (u_int64_t)(philo->data->time_die);
	print_msg("is eating", philo);
	philo->eating = 1;
	ft_usleep(philo->data->time_eat);
	philo->eating = 0;
	philo->eat_count++;
	drop_forks(philo);
}
