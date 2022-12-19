/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:45:22 by bgrulois          #+#    #+#             */
/*   Updated: 2022/09/25 15:00:53 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

pthread_mutex_t	*init_mutex(void)
{
	pthread_mutex_t	*mutex;

	mutex = malloc(sizeof(pthread_mutex_t));
	if (!mutex)
		return (NULL);
	pthread_mutex_init(mutex, NULL);
	return (mutex);
}

void	init_forks(t_global *global, t_philo **philos, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		if (i != 0)
		{
			philos[i]->fork_left = global->forks_mutexes[i - 1];
			philos[i]->fork_right = global->forks_mutexes[i];
		}
		i++;
	}
	philos[0]->fork_right = global->forks_mutexes[0];
	philos[0]->fork_left = global->forks_mutexes[i - 1];
	return ;
}

t_philo	**init_philos(t_global *global, char **av)
{
	int		i;
	t_philo	**philos;

	i = -1;
	philos = malloc(sizeof(t_philo *) * ft_atoi(av[1]));
	if (!philos)
		return (NULL);
	while (++i < ft_atoi(av[1]))
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (NULL);
		philos[i]->philo_data_race = init_mutex();
		philos[i]->meals_mutex = init_mutex();
		philos[i]->id = i;
		philos[i]->meals_eaten = 0;
		philos[i]->gs = global;
		philos[i]->death_time = global->time_to_die;
	}
	init_forks(global, philos, av);
	return (philos);
}

void	reset_global_vals(t_global *global, char **av)
{
	(void)av;
	global->n_philos = 0;
	global->start = 0;
	global->time_to_die = 0;
	global->time_to_eat = 0;
	global->time_to_sleep = 0;
	global->n_meals = 0;
	global->a_philo_is_dead = 0;
	return ;
}

t_global	*init_global(char **av)
{
	t_global	*global;
	int			i;

	global = malloc(sizeof(t_global));
	if (!global)
		return (NULL);
	global->forks_mutexes = malloc(sizeof(pthread_mutex_t *) * ft_atoi(av[1]));
	if (!global->forks_mutexes)
		return (NULL);
	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		global->forks_mutexes[i] = malloc(sizeof(pthread_mutex_t));
		if (!global->forks_mutexes[i])
			return (NULL);
		pthread_mutex_init(global->forks_mutexes[i], NULL);
	}
	global->display = malloc(sizeof(pthread_mutex_t));
	global->death_mutex = malloc(sizeof(pthread_mutex_t));
	if (!global->death_mutex || !global->display)
		return (NULL);
	reset_global_vals(global, av);
	pthread_mutex_init(global->death_mutex, NULL);
	pthread_mutex_init(global->display, NULL);
	return (global);
}
