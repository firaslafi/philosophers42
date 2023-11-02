
#include "./philosophers.h"

// check args all num and verify input values
int	ft_checkallnumvals(char **str)
{
	int	i;

	i = 1;
	if (ft_atoi(str[1]) > 200)
		ft_error("Input Error: more than 200 philo");
	if (ft_atoi(str[2]) <= 0 || ft_atoi(str[3]) <= 0 || ft_atoi(str[3]) <= 0
		|| ft_atoi(str[4]) <= 0)
		ft_error("Input Error: negative or zero value");
	while (str[i])
	{
		if (!ft_isalldigit(str[i]))
            ft_error("Input Error: not numeric");
		i++;
	}
	return (0);
}
int	main(int argc, char **argv)
{
	// fix paths for 5 or 6
	if (argc == 5)
	{
	    ft_checkallnumvals(argv);
        
	}
	else
	{
        ft_error("Input Error: args number");
	}
	// two paths design for 5 and 4 args
	return (EXIT_SUCCESS);
}