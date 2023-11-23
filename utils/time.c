

#include "../philosophers.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}
u_int64_t	ft_usleep(u_int64_t milliseconds)
{
	u_int64_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(50);
	return (0);
}

u_int64_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_putstr_fd("Failed to get time\n", 2);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}