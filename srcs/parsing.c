/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:33:03 by bgrulois          #+#    #+#             */
/*   Updated: 2022/09/18 18:17:45 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ft_isdigit(char c)
{
	if (c < '0' || c > '9')
		return (-1);
	return (0);
}

int	check_args_validity(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) == -1)
				return (-1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	atoi_all_args(int ac, char **av, t_global *global)
{
	global->n_philos = ft_atoi(av[1]);
	global->time_to_die = ft_atoi(av[2]);
	global->time_to_eat = ft_atoi(av[3]);
	global->time_to_sleep = ft_atoi(av[4]);
	if (global->time_to_die < 0
		|| global->time_to_eat < 0 || global->time_to_sleep < 0)
		return (-1);
	if (ac == 6)
		global->n_meals = ft_atoi(av[5]);
	return (0);
}

int	ft_parsing(int ac, char **av, t_global *global)
{
	if (global == NULL)
		return (-1);
	if (check_args_validity(ac, av) == -1)
		return (-1);
	if (atoi_all_args(ac, av, global) == -1)
		return (-1);
	return (0);
}
