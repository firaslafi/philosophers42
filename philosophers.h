


#ifndef PHILOSOPHOERS_H
# define PHILOSOPHOERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <pthread.h>
# include <inttypes.h>
# include <sys/time.h>

struct s_program;

typedef struct s_mem_block
{
 void    *block_pointer;
 struct s_mem_block *next;
}      t_mem_block;

typedef struct s_philo
{
	struct s_program	*data;
	pthread_t		t1;
	int				id;
	int				eat_count;
	// int				status;
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
void	ft_error(char *msg, t_mem_block **lst);
void *ft_malloc(t_mem_block **lst, int size);
void ft_free_all(t_mem_block **lst);
void	ft_error_init(char *msg, t_mem_block **lst, t_program *progdata);
size_t	get_current_time(void);

#endif