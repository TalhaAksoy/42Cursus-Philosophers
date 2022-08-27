/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_locks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saksoy <saksoy@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:19:12 by saksoy            #+#    #+#             */
/*   Updated: 2022/08/26 22:33:06 by saksoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_fork_using(t_data *data, t_philo *philo, char c)
{
	if (c == 'L' && philo->lf != 1)
	{
		pthread_mutex_lock(&(data->forks[philo->left_fork]));
		if (data->using_forks[philo->left_fork] != 0)
		{
			pthread_mutex_unlock(&(data->forks[philo->left_fork]));
			return (1);
		}
		ft_lock_forks(data, philo, 'L');
		pthread_mutex_unlock(&(data->forks[philo->left_fork]));
		return (0);
	}
	else if (c == 'R' && philo->rf != 1)
	{
		pthread_mutex_lock(&(data->forks[philo->right_fork]));
		if (data->using_forks[philo->right_fork] != 0)
		{
			pthread_mutex_unlock(&(data->forks[philo->right_fork]));
			return (1);
		}
		ft_lock_forks(data, philo, 'R');
		pthread_mutex_unlock(&(data->forks[philo->right_fork]));
		return (0);
	}
	return (0);
}

int	ft_lock_forks(t_data *data, t_philo *philo, char c)
{
	if (c == 'L')
	{
		data->using_forks[philo->left_fork] = 1;
		philo->lf = 1;
		ft_print_info(philo, get_tick_count(), STATE_TAKEN_FORKS);
	}
	else if (c == 'R')
	{
		data->using_forks[philo->right_fork] = 1;
		philo->rf = 1;
		ft_print_info(philo, get_tick_count(), STATE_TAKEN_FORKS);
	}
	return (0);
}

void	ft_unlock_forks(t_data *data, t_philo *philo, char c)
{
	if (c == 'L')
	{
		philo->lf = 0;
		pthread_mutex_lock(&(data->forks[philo->left_fork]));
		data->using_forks[philo->left_fork] = 0;
		pthread_mutex_unlock(&(data->forks[philo->left_fork]));
	}
	else if (c == 'R')
	{
		philo->rf = 0;
		pthread_mutex_lock(&(data->forks[philo->right_fork]));
		data->using_forks[philo->right_fork] = 0;
		pthread_mutex_unlock(&(data->forks[philo->right_fork]));
	}
}
