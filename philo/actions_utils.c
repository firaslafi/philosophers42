/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:12:09 by flafi             #+#    #+#             */
/*   Updated: 2023/11/28 17:13:12 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock);
	return (0);
}

void	print_msg(char *msg, t_philo *philo)
{
	long	action_time;

	action_time = get_current_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write);
	if (!check_dead(philo))
		printf("%ld %d %s\n", action_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->write);
}
