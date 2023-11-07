


#ifndef PHILOSOPHOERS_H
# define PHILOSOPHOERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <pthread.h>
# include <inttypes.h>

struct s_program;

typedef struct s_philo
{
	struct s_program	*data;
	pthread_t		t1;
	int				id;
	int				eat_cont;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_program
{
	pthread_t		*th_id;
	int				num_philos;
	int				num_meals;
	int				dead;
	int				finished;
	t_philo			*philos;
	size_t		time_die;
	size_t		time_eat;
	size_t		time_sleep;
	size_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}					t_program;



int	ft_isdigit(int c);
int ft_isalldigit(char *str);
int	ft_atoi(char *str);
void	ft_error(char *msg);

#endif