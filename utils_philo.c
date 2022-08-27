/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saksoy <saksoy@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:19:22 by saksoy            #+#    #+#             */
/*   Updated: 2022/08/26 19:13:08 by saksoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_get_forks_num(t_philo *philo, t_data *data)
{
	if (philo->who_am_i == 0)
		philo->left_fork = data->total_philos - 1;
	else
		philo->left_fork = philo->who_am_i - 1;
	philo->right_fork = philo->who_am_i;
}

size_t	ft_get_philo_num(t_data *data)
{
	size_t	id;

	pthread_mutex_lock(&(data->mutex));
	data->count_philos += 2;
	if (data->count_philos > data->total_philos)
		data->count_philos = 2;
	id = data->count_philos;
	pthread_mutex_unlock(&(data->mutex));
	return (id);
}

void	ft_print_info(t_philo *p, t_time now, int c)
{
	if (c == STATE_EAT)
		printf("%llu %d is eating\n", now - p->start_time, p->who_am_i + 1);
	else if (c == STATE_SLEEP)
		printf("%llu %d is sleeping\n", now - p->start_time, p->who_am_i + 1);
	else if (c == STATE_THINK)
		printf("%llu %d is thinking\n", now - p->start_time, p->who_am_i + 1);
	else if (c == STATE_DEAD)
		printf("%llu %d is dead\n", now - p->start_time, p->who_am_i + 1);
	else if (c == STATE_TAKEN_FORKS)
		printf("%llu %d is taken forks\n", \
			now - p->start_time, p->who_am_i + 1);
}

t_time	get_tick_count(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	smart_sleep(t_time sleep_time)
{
	t_time	start;

	start = get_tick_count();
	while (1)
	{
		if (get_tick_count() - start >= sleep_time)
			break ;
		usleep(50);
	}
}
