/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:50:29 by flafi             #+#    #+#             */
/*   Updated: 2023/11/28 17:56:59 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_exit(t_program *progdata)
{
	int	i;

	i = 0;
	while (i < progdata->num_philos)
	{
		pthread_mutex_destroy(&progdata->forks[i]);
		pthread_mutex_destroy(&progdata->philos[i].lock);
		i++;
	}
	pthread_mutex_destroy(&progdata->write);
	pthread_mutex_destroy(&progdata->lock);
}

void	ft_error(char *msg, t_mem_block **lst)
{
	printf("%s\n", msg);
	ft_free_all(lst);
	exit(EXIT_FAILURE);
}

void	ft_error_init(char *msg, t_mem_block **lst, t_program *progdata)
{
	if (msg)
		printf("%s\n", msg);
	if (progdata)
		ft_exit(progdata);
	ft_free_all(lst);
	exit(EXIT_FAILURE);
}
