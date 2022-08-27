/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saksoy <saksoy@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:19:15 by saksoy            #+#    #+#             */
/*   Updated: 2022/08/26 22:57:24 by saksoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_kill_all_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->total_philos)
	{
		pthread_mutex_lock(&data->dead_mutex[i]);
		data->dead_list[i] = STATE_DEAD;
		pthread_mutex_unlock(&data->dead_mutex[i]);
	}
	smart_sleep(1);
}

int	ft_is_did_reach_eat_limit(t_data *data, t_controller *vars)
{
	pthread_mutex_lock(&(data->mutex));
	if (data->eat_count == vars->eat_limit)
	{
		pthread_mutex_unlock(&(data->mutex));
		vars->eat_termination = 1;
		vars->termination_t = get_tick_count();
		return (1);
	}
	pthread_mutex_unlock(&(data->mutex));
	return (0);
}

void	*controller(void *p_data)
{
	t_data			*data;
	t_controller	vars;
	int				sum;

	data = (t_data *)p_data;
	sum = data->total_philos * data->eat_limit;
	vars.total_philos = data->total_philos;
	vars.eat_limit = data->eat_limit * vars.total_philos;
	vars.eat_termination = 0;
	vars.dead_termination = 0;
	while (1)
	{
		if (ft_is_did_reach_eat_limit(data, &vars))
			break ;
		if (ft_is_anyone_dead(data, &vars))
			break ;
	}
	ft_kill_all_philos(data);
	if (vars.eat_termination)
		printf("%llu %d spaghetti has been served\n", \
			vars.termination_t - data->start_time, sum);
	else if (vars.dead_termination)
		printf("%llu %d is dead\n", vars.termination_t - data->start_time, \
			vars.dead_philo_id + 1);
	return (NULL);
}
