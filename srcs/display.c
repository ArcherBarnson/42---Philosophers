/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:03:38 by bgrulois          #+#    #+#             */
/*   Updated: 2022/09/10 16:30:01 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	print_msg(t_philo *philo, int mode)
{
	int		current_time;
	char	*n;
	char	*timestamp;

	current_time = get_timestamp(philo->gs);
	n = ft_itoa(philo->id + 1);
	timestamp = ft_itoa(current_time);
	write(1, timestamp, ft_strlen(timestamp));
	write(1, " ", 1);
	write(1, n, ft_strlen(n));
	write(1, " ", 1);
	if (mode == 0)
		write(1, "has taken a fork\n", 17);
	if (mode == 1)
		write(1, "is thinking\n", 12);
	if (mode == 2)
		write(1, "is eating\n", 10);
	if (mode == 3)
		write(1, "is sleeping\n", 12);
	if (mode == -1)
		write(1, "died\n", 5);
	free(n);
	free(timestamp);
	return ;
}

void	display_ctl(t_philo *philo, int mode)
{
	int	state;

	pthread_mutex_lock(philo->gs->death_mutex);
	state = philo->gs->a_philo_is_dead;
	pthread_mutex_unlock(philo->gs->death_mutex);
	if (state == 0)
	{
		pthread_mutex_lock(philo->gs->display);
		print_msg(philo, mode);
		pthread_mutex_unlock(philo->gs->display);
	}
	return ;
}
