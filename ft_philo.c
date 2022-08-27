/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saksoy <saksoy@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:19:11 by saksoy            #+#    #+#             */
/*   Updated: 2022/08/26 22:20:52 by saksoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophers(void *p_data)
{
	t_data	*data;
	t_philo	philo;

	data = (t_data *)p_data;
	philo.who_am_i = ft_get_philo_num(data) - 1;
	ft_get_forks_num(&philo, data);
	philo.start_time = data->start_time;
	philo.last_eat_time = philo.start_time;
	if (philo.who_am_i == 0 && data->total_philos == 1)
	{
		ft_lock_forks(data, &philo, 'R');
		smart_sleep(data->time_to_die);
		ft_kill_all_philos(data);
		return (NULL);
	}
	while (1)
	{
		if (ft_eating_spaghetti(data, &philo) == STATE_DEAD)
			break ;
		if (ft_sleeping(data, &philo) == STATE_DEAD)
			break ;
		if (ft_thinking(data, &philo) == STATE_DEAD)
			break ;
	}
	return (NULL);
}

int	ft_eating_spaghetti(t_data *data, t_philo *ph)
{
	while (ft_is_fork_using(data, ph, 'L') || ft_is_fork_using(data, ph, 'R'))
	{
		usleep(10);
		if (get_tick_count() - ph->last_eat_time >= (t_time)data->time_to_die)
		{
			ft_death_call(data, ph);
			return (STATE_DEAD);
		}
		else if (ft_dead_check(data, ph->who_am_i) == STATE_DEAD)
			return (STATE_DEAD);
	}
	pthread_mutex_lock(&(data->mutex));
	data->eat_count++;
	pthread_mutex_unlock(&(data->mutex));
	ft_print_info(ph, get_tick_count(), STATE_EAT);
	ph->last_eat_time = get_tick_count();
	smart_sleep(data->time_to_eat);
	ft_unlock_forks(data, ph, 'L');
	ft_unlock_forks(data, ph, 'R');
	return (0);
}

int	ft_sleeping(t_data *data, t_philo *philo)
{
	t_time	life_time;

	life_time = get_tick_count() - philo->last_eat_time;
	if (ft_dead_check(data, philo->who_am_i) == STATE_DEAD)
		return (STATE_DEAD);
	if (life_time + data->time_to_sleep > data->time_to_die)
	{
		ft_print_info(philo, get_tick_count(), STATE_SLEEP);
		smart_sleep(data->time_to_die - life_time);
		ft_death_call(data, philo);
		return (STATE_DEAD);
	}
	ft_print_info(philo, get_tick_count(), STATE_SLEEP);
	smart_sleep(data->time_to_sleep);
	return (0);
}

int	ft_thinking(t_data *data, t_philo *philo)
{
	if (ft_dead_check(data, philo->who_am_i) == STATE_DEAD)
		return (STATE_DEAD);
	ft_print_info(philo, get_tick_count(), STATE_THINK);
	return (0);
}
