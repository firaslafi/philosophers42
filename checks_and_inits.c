/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_and_inits.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:15:22 by flafi             #+#    #+#             */
/*   Updated: 2023/11/28 17:17:28 by flafi            ###   ########.fr       */
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
	progdata->th_id = ft_malloc(lst, (progdata->num_philos
				* sizeof(pthread_t)));
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

void	init_forks(t_program *progdata)
{
	int	i;

	i = 0;
	while (i < progdata->num_philos)
	{
		pthread_mutex_init(&progdata->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < progdata->num_philos)
	{
		progdata->philos[i].l_fork = &progdata->forks[i];
		progdata->philos[i].r_fork = &progdata->forks[(i + 1)
			% progdata->num_philos];
		i++;
	}
}

void	init_philos(t_program *progdata)
{
	int	i;

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
