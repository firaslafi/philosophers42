/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:06:35 by flafi             #+#    #+#             */
/*   Updated: 2023/11/28 17:45:36 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <errno.h>
# include <inttypes.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_program;

typedef struct mem_block
{
	void				*block_pointer;
	struct mem_block	*next;
}						t_mem_block;

typedef struct s_philo
{
	struct s_program	*data;
	pthread_t			t1;
	int					id;
	int					eat_count;
	int					eating;
	long				time_to_kill;
	pthread_mutex_t		lock;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
}						t_philo;

typedef struct s_program
{
	pthread_t			*th_id;
	pthread_t			th_sup;
	int					num_philos;
	int					num_meals;
	int					dead;
	int					finished;
	t_philo				*philos;
	size_t				time_die;
	size_t				time_eat;
	size_t				time_sleep;
	size_t				start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		lock;
	pthread_mutex_t		write;
}						t_program;

int						ft_isdigit(int c);
int						ft_isalldigit(char *str);
long					ft_atoi(char *str);
void					ft_error(char *msg, t_mem_block **lst);
void					*ft_malloc(t_mem_block **lst, int size);
void					ft_free_all(t_mem_block **lst);
void					ft_error_init(char *msg, t_mem_block **lst,
							t_program *progdata);
long					get_current_time(void);
long					ft_usleep(long milliseconds);
void					ft_exit(t_program *progdata);
void					print_msg(char *msg, t_philo *philo);
void					eat(t_philo *philo);
int						check_dead(t_philo *philo);
void					kill_program(t_program *data);
void					update_kill_time(t_philo *philo);
int						ate_all_meals(t_philo *philo);
int						ft_checkallnumvals(char **str, int argc,
							t_mem_block **lst);
void					fill_progdata(t_program *progdata, char **argv,
							int argc);
void					alloc_prog(t_program *progdata, t_mem_block **lst);
void					init_forks(t_program *progdata);
void					init_philos(t_program *progdata);
int						case_one(t_program *progdata, t_mem_block **lst);
void					print_msg_adj(t_philo *philo);

#endif