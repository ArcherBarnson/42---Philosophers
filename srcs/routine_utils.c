/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 16:39:03 by bgrulois          #+#    #+#             */
/*   Updated: 2022/09/10 17:50:45 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	meals_limit_reached(t_philo **philos)
{
	int	i;
	int	meals;
	int	meals_eaten;

	i = 0;
	meals = 0;
	if (philos[0]->gs->n_meals == 0)
		return (0);
	while (i < philos[0]->gs->n_philos)
	{
		pthread_mutex_lock(philos[i]->meals_mutex);
		meals_eaten = philos[i]->meals_eaten;
		pthread_mutex_unlock(philos[i]->meals_mutex);
		if (meals_eaten >= philos[0]->gs->n_meals)
			meals++;
		i++;
	}
	if (meals >= philos[0]->gs->n_philos)
		return (1);
	return (0);
}

int	all_meals_eaten(t_philo *philo)
{
	pthread_mutex_lock(philo->gs->death_mutex);
	philo->gs->a_philo_is_dead = 1;
	pthread_mutex_unlock(philo->gs->death_mutex);
	return (-1);
}

int	a_philo_died(t_philo *philo)
{
	pthread_mutex_lock(philo->gs->death_mutex);
	philo->gs->a_philo_is_dead = 1;
	pthread_mutex_unlock(philo->gs->death_mutex);
	print_msg(philo, -1);
	return (-1);
}
