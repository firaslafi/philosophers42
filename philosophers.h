


#ifndef PHILOSOPHOERS_H
# define PHILOSOPHOERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <pthread.h>
# include <inttypes.h>

struct	s_data; 

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t       t1;
	int             id;
	int             eat_cont;
	int             status;
	int             eating;
	uint64_t        time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
} t_philo;

typedef struct s_data
{
	pthread_t       *tid;
	int             philo_num;
	int             meals_nb;
	int             dead;
	int             finished;
	t_philo         *philos;
	u_int64_t       death_time;
	u_int64_t       eat_time;
	u_int64_t       sleep_time;
	u_int64_t       start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t lock;
	pthread_mutex_t write;
} t_data;


int	ft_isdigit(int c);
int ft_isalldigit(char *str);
int	ft_atoi(char *str);
void	ft_error(char *msg);

#endif