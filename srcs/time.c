/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:48:48 by bgrulois          #+#    #+#             */
/*   Updated: 2022/09/08 14:24:02 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

long unsigned	get_timestamp(t_global *global)
{
	struct timeval	time;
	long unsigned	timestamp;

	gettimeofday(&time, NULL);
	if (global == NULL)
		timestamp = time.tv_sec * 1000 + time.tv_usec / 1000;
	else
	{
		timestamp = time.tv_sec * 1000 + time.tv_usec / 1000;
		timestamp -= global->start;
	}
	return (timestamp);
}
