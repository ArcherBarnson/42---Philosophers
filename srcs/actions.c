/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:32:43 by bgrulois          #+#    #+#             */
/*   Updated: 2022/09/25 16:12:39 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	sleep_tight(t_philo *philo, unsigned long t)
{
	unsigned long	start;
	unsigned long	cmp;
	int				state;

	start = get_timestamp(philo->gs);
	cmp = get_timestamp(philo->gs);
	state = 0;
	while (cmp - start < t)
	{
		usleep(200);
		pthread_mutex_lock(philo->gs->death_mutex);
		state = philo->gs->a_philo_is_dead;
		pthread_mutex_unlock(philo->gs->death_mutex);
		if (state == 1)
			break ;
		cmp = get_timestamp(philo->gs);
	}
	pthread_mutex_lock(philo->gs->death_mutex);
	state = philo->gs->a_philo_is_dead;
	pthread_mutex_unlock(philo->gs->death_mutex);
	if (state == 1)
		return ;
	usleep(t);
	return ;
}

void	thinking(t_philo *philo)
{
	display_ctl(philo, 1);
	return ;
}

void	eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_left);
		display_ctl(philo, 0);
		pthread_mutex_lock(philo->fork_right);
		display_ctl(philo, 0);
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		display_ctl(philo, 0);
		pthread_mutex_lock(philo->fork_left);
		display_ctl(philo, 0);
	}
	display_ctl(philo, 2);
	pthread_mutex_lock(philo->philo_data_race);
	philo->death_time = get_timestamp(philo->gs) + philo->gs->time_to_die;
	pthread_mutex_unlock(philo->philo_data_race);
	sleep_tight(philo, (unsigned long)philo->gs->time_to_eat);
	pthread_mutex_lock(philo->meals_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meals_mutex);
	return ;
}

void	sleeping(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
	}
	display_ctl(philo, 3);
	sleep_tight(philo, (unsigned long)philo->gs->time_to_sleep);
	return ;
}
