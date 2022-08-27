/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saksoy <saksoy@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:19:17 by saksoy            #+#    #+#             */
/*   Updated: 2022/08/26 18:19:18 by saksoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *str)
{
	printf("%s", str);
	return (-1);
}

int	ft_checkarg(char *str)
{
	long	res;

	res = 0;
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (ft_error("Error\n"));
		res = res * 10 + *str - '0';
		if (res > __INT_MAX__)
			return (ft_error("Error\n"));
		str++;
	}
	return ((int)res);
}

int	ft_checkargs(int ac, char **av, t_data *data)
{
	data->eat_limit = -2;
	if (ac != 6 && ac != 5)
		return (-1);
	while (--ac)
	{
		if (ac == 5)
			data->eat_limit = ft_checkarg(av[ac]);
		else if (ac == 4)
			data->time_to_sleep = ft_checkarg(av[ac]);
		else if (ac == 3)
			data->time_to_eat = ft_checkarg(av[ac]);
		else if (ac == 2)
			data->time_to_die = ft_checkarg(av[ac]);
		else
			data->total_philos = ft_checkarg(av[ac]);
	}
	if (data->time_to_sleep == -1 || data->time_to_eat == -1
		|| data->time_to_die == -1 || data->total_philos < 1
		|| data->eat_limit == -1)
		return (ft_error("ARG PROBLEM"));
	if (data->eat_limit == 0)
		return (-1);
	return (0);
}
