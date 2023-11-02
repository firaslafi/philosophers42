
#include "../philosophers.h"

int	ft_isdigit(int c)

{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int ft_isalldigit(char *str)
{
	int i;
	i = 0;

	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}