/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:51:33 by bgrulois          #+#    #+#             */
/*   Updated: 2022/09/25 16:07:42 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	free_philos(t_philo **philos, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		philos[i]->gs = NULL;
		philos[i]->fork_left = NULL;
		philos[i]->fork_right = NULL;
		pthread_mutex_destroy(philos[i]->meals_mutex);
		pthread_mutex_destroy(philos[i]->philo_data_race);
		free(philos[i]->fork_left);
		free(philos[i]->fork_right);
		free(philos[i]->thread);
		free(philos[i]->meals_mutex);
		free(philos[i]->philo_data_race);
		free(philos[i]->gs);
		free(philos[i]);
		i++;
	}
	free(philos);
	return ;
}

void	free_global(t_global *gs, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(gs->forks_mutexes[i]);
		free(gs->forks_mutexes[i]);
		i++;
	}
	pthread_mutex_destroy(gs->display);
	pthread_mutex_destroy(gs->death_mutex);
	free(gs->forks_mutexes);
	free(gs->display);
	free(gs->death_mutex);
	free(gs);
	return ;
}

void	free_all(t_global *global, t_philo **philos)
{
	int	n;

	n = global->n_philos;
	free_philos(philos, n);
	free_global(global, n);
	return ;
}
