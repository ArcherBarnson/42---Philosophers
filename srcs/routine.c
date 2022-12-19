/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:21:02 by bgrulois          #+#    #+#             */
/*   Updated: 2022/09/28 09:59:20 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ft_death(t_philo **philos)
{
	int				i;
	long unsigned	death_time;
	long unsigned	current_time;
	int				meals_sw;

	i = -1;
	meals_sw = 0;
	while (++i < philos[0]->gs->n_philos)
	{
		current_time = get_timestamp(philos[0]->gs);
		pthread_mutex_lock(philos[i]->philo_data_race);
		death_time = philos[i]->death_time;
		pthread_mutex_unlock(philos[i]->philo_data_race);
		meals_sw = meals_limit_reached(philos);
		if (meals_sw == 1)
			return (all_meals_eaten(philos[0]));
		if (current_time >= death_time)
			return (a_philo_died(philos[i]));
	}
	return (0);
}

void	*ft_alt_routine(void *arg)
{
	t_philo	*philo;
	int		death_state;

	philo = (t_philo *)arg;
	death_state = 0;
	display_ctl(philo, 0);
	while (death_state == 0)
	{
		pthread_mutex_lock(philo->gs->death_mutex);
		death_state = philo->gs->a_philo_is_dead;
		pthread_mutex_unlock(philo->gs->death_mutex);
	}
	return (NULL);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	int		death_state;

	philo = (t_philo *)arg;
	death_state = 0;
	pthread_mutex_lock(philo->gs->death_mutex);
	death_state = philo->gs->a_philo_is_dead;
	pthread_mutex_unlock(philo->gs->death_mutex);
	if (philo->id % 2 != 0)
		usleep(100);
	while (death_state == 0)
	{
		eating(philo);
		sleeping(philo);
		usleep(300);
		thinking(philo);
		pthread_mutex_lock(philo->gs->death_mutex);
		death_state = philo->gs->a_philo_is_dead;
		pthread_mutex_unlock(philo->gs->death_mutex);
		usleep(100);
	}
	return (NULL);
}
