/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_dead.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saksoy <saksoy@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:19:16 by saksoy            #+#    #+#             */
/*   Updated: 2022/08/26 18:19:17 by saksoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_anyone_dead(t_data *data, t_controller *vars)
{
	int	philo_id;

	philo_id = -1;
	while (++philo_id < vars->total_philos)
	{
		if (ft_dead_check(data, philo_id) == STATE_DEAD)
		{
			vars->dead_philo_id = philo_id;
			vars->termination_t = get_tick_count();
			vars->dead_termination = 1;
			return (1);
		}
	}
	return (0);
}

int	ft_dead_check(t_data *data, int philo_id)
{
	pthread_mutex_lock(&(data->dead_mutex[philo_id]));
	if (data->dead_list[philo_id] == STATE_DEAD)
	{
		pthread_mutex_unlock(&data->dead_mutex[philo_id]);
		return (STATE_DEAD);
	}
	pthread_mutex_unlock(&data->dead_mutex[philo_id]);
	return (0);
}

int	ft_death_call(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->dead_mutex[philo->who_am_i]);
	data->dead_list[philo->who_am_i] = STATE_DEAD;
	pthread_mutex_unlock(&data->dead_mutex[philo->who_am_i]);
	return (STATE_DEAD);
}
