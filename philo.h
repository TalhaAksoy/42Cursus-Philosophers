/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saksoy <saksoy@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:19:20 by saksoy            #+#    #+#             */
/*   Updated: 2022/08/26 22:25:59 by saksoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

# define STATE_EAT 1
# define STATE_SLEEP 2
# define STATE_THINK 3
# define STATE_DEAD 4
# define STATE_TAKEN_FORKS 5

typedef long long	t_time;

typedef struct s_controller
{
	int		total_philos;
	int		eat_limit;
	int		eat_termination;
	int		dead_termination;
	int		dead_philo_id;
	t_time	termination_t;
}	t_controller;

typedef struct s_philo
{
	int		who_am_i;
	int		left_fork;
	int		right_fork;
	int		rf;
	int		lf;
	t_time	start_time;
	t_time	last_eat_time;
}	t_philo;

typedef struct s_data
{
	long long		total_philos;
	long long		count_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		eat_limit;
	long long		eat_count;
	int				*using_forks;
	int				*dead_list;
	t_time			start_time;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex;
}	t_data;

t_time	get_tick_count(void);
void	smart_sleep(t_time sleep_time);

int		ft_error(char *str);
int		ft_checkarg(char *str);
int		ft_checkargs(int ac, char **av, t_data *philo);

void	*controller(void *p_data);
void	ft_kill_all_philos(t_data *data);
int		ft_is_anyone_dead(t_data *data, t_controller *vars);
int		ft_is_did_reach_eat_limit(t_data *data, t_controller *vars);

int		ft_init(t_data *data);
void	ft_destroy(t_data *data, pthread_t **philos);
int		mutexs_init(pthread_mutex_t **mutexs, size_t size);
int		ft_create_thread(t_data *data, pthread_t *philos);

size_t	ft_get_philo_num(t_data *data);
void	ft_get_forks_num(t_philo *philo, t_data *data);

void	*philosophers(void *p_data);
int		ft_thinking(t_data *data, t_philo *philo);
int		ft_sleeping(t_data *data, t_philo *philo);
int		ft_eating_spaghetti(t_data *data, t_philo *philo);

int		ft_death_call(t_data *data, t_philo *philo);
int		ft_dead_check(t_data *data, int philo_id);

int		ft_lock_forks(t_data *data, t_philo *philo, char c);
void	ft_unlock_forks(t_data *data, t_philo *philo, char c);
int		ft_is_fork_using(t_data *data, t_philo *philo, char c);

void	ft_print_info(t_philo *p, t_time now, int c);

#endif