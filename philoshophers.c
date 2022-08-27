/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoshophers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saksoy <saksoy@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:19:21 by saksoy            #+#    #+#             */
/*   Updated: 2022/08/27 03:29:14 by saksoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_create_thread(t_data *data, pthread_t *philos)
{
	int	i;

	i = 0;
	while (i < data->total_philos)
	{
		if (pthread_create(philos + i, NULL, philosophers, data) != 0)
			return (-1);
		usleep(100);
		i += 2;
	}
	i = 1;
	while (i < data->total_philos)
	{
		if (pthread_create(&philos[i], NULL, philosophers, data) != 0)
			return (-1);
		usleep(100);
		i += 2;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	*philos;
	pthread_t	death_controller;
	int			i;

	i = -1;
	if (ft_checkargs(ac, av, &data) == -1)
		return (-1);
	philos = malloc(sizeof(pthread_t) * data.total_philos);
	if (ft_init(&data) == -1)
		return (ft_error("Init Error\n"));
	data.start_time = get_tick_count();
	if (pthread_create(&death_controller, NULL, controller, &data) != 0)
		return (-1);
	if (ft_create_thread(&data, philos) == -1)
		return (ft_error("Thread Creating Error\n"));
	while (++i < data.total_philos)
		pthread_join(philos[i], NULL);
	pthread_join(death_controller, NULL);
	ft_destroy(&data, &philos);
}
