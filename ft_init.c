/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saksoy <saksoy@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:19:14 by saksoy            #+#    #+#             */
/*   Updated: 2022/08/26 18:39:29 by saksoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init(t_data *data)
{
	int	i;

	i = -1;
	data->dead_list = malloc(sizeof(int) * data->total_philos);
	data->using_forks = malloc(sizeof(int) * data->total_philos);
	if (!(data->using_forks) || !(data->dead_list))
		return (-1);
	if (mutexs_init(&(data->dead_mutex), data->total_philos) == -1)
		return (-1);
	if (pthread_mutex_init(&(data->mutex), 0) == -1)
		return (-1);
	if (mutexs_init(&(data->forks), data->total_philos) == -1)
		return (-1);
	data->count_philos = -1;
	data->eat_count = 0;
	memset(data->using_forks, 0, sizeof(int) * data->total_philos);
	memset(data->dead_list, 0, sizeof(int) * data->total_philos);
	return (0);
}

int	mutexs_init(pthread_mutex_t **mutexs, size_t size)
{
	if (size == 0)
	{
		if (pthread_mutex_init(*mutexs, NULL) != 0)
			return (-1);
	}
	else
	{
		*mutexs = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * size);
		if (!(*mutexs))
			return (-1);
		while (size--)
			if (pthread_mutex_init(&((*mutexs)[size]), NULL) != 0)
				return (-1);
	}
	return (0);
}

void	ft_destroy(t_data *data, pthread_t **philos)
{
	int	i;

	i = -1;
	while (++i < data->total_philos)
	{
		pthread_mutex_destroy(&(data->dead_mutex[i]));
		pthread_mutex_destroy(&(data->forks[i]));
	}
	pthread_mutex_destroy(&(data->mutex));
	free(data->dead_list);
	free(data->dead_mutex);
	free(data->using_forks);
	free(data->forks);
	free(*philos);
}
