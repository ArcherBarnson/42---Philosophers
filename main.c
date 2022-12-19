/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:35:35 by bgrulois          #+#    #+#             */
/*   Updated: 2022/09/25 15:58:55 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_threads(t_philo **philos)
{
	int	i;
	int	n;

	i = 0;
	n = philos[0]->gs->n_philos;
	while (i < n)
	{
		philos[i]->thread = malloc(sizeof(pthread_t));
		if (!philos[i]->thread)
			return ;
		i++;
	}
	return ;
}

t_global	*main_check(int ac, char **av)
{
	t_global	*gs;

	if (ac < 5 || ac > 6 || (ac == 6 && ft_atoi(av[5]) <= 0)
		|| ft_atoi(av[1]) <= 0)
		return (NULL);
	gs = init_global(av);
	if (ft_parsing(ac, av, gs) == -1)
	{
		free_global(gs, ft_atoi(av[1]));
		return (NULL);
	}
	return (gs);
}

void	start_threads(t_philo **philos)
{
	int	i;

	i = -1;
	if (philos[0]->gs->n_philos == 1)
		pthread_create(philos[0]->thread, NULL,
			&ft_alt_routine, philos[0]);
	else
	{
		while (++i < philos[0]->gs->n_philos)
			pthread_create(philos[i]->thread, NULL,
				&ft_routine, philos[i]);
	}
	return ;
}

int	main(int ac, char **av)
{
	t_global	*gs;
	t_philo		**philos;
	int			i;

	gs = main_check(ac, av);
	if (gs == NULL)
		return (-1);
	philos = init_philos(gs, av);
	if (philos == NULL)
		return (-1);
	set_threads(philos);
	gs->start = get_timestamp(NULL);
	start_threads(philos);
	while (ft_death(philos) == 0)
		;
	i = -1;
	while (++i < philos[0]->gs->n_philos)
		pthread_join(*philos[i]->thread, NULL);
	free_all(gs, philos);
	return (0);
}
