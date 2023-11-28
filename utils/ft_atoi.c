/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:50:16 by flafi             #+#    #+#             */
/*   Updated: 2023/11/28 16:50:21 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	ft_isspace(const char *str)
{
	if (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\f'
		|| *str == '\r' || *str == '\v')
		return (1);
	return (0);
}

static int	ft_issign(const char *str)
{
	if (*str == '-' || *str == '+')
		return (1);
	return (0);
}

long	ft_atoi(char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (ft_isspace(str))
	{
		str++;
	}
	if (ft_issign(str))
	{
		if (*str == '-')
		{
			sign *= -1;
			str++;
		}
		else
			str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}
