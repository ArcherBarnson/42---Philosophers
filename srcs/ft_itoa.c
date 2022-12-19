/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:14:59 by bgrulois          #+#    #+#             */
/*   Updated: 2022/09/10 16:31:24 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	malloc_get_size(int n)
{
	int		c;
	long	nb;

	c = 0;
	nb = n;
	if (n < 0)
	{
		c++;
		nb = -1 * (long)n;
	}
	while (nb > 9)
	{
		nb /= 10;
		c++;
	}
	return (c + 1);
}

char	*ft_itoa(int n)
{
	long long	nb;
	int			mlen;
	char		*returnstr;

	mlen = malloc_get_size(n);
	nb = n;
	returnstr = malloc(sizeof(char) * (mlen + 1));
	if (!(returnstr))
		return (NULL);
	if (n < 0)
	{
		nb = -1 * (long long) n;
		returnstr[0] = '-';
	}
	returnstr[mlen] = '\0';
	mlen--;
	while (nb > 9)
	{
		returnstr[mlen] = (nb % 10) + '0';
		nb /= 10;
		mlen--;
	}
	returnstr[mlen] = nb + '0';
	return (returnstr);
}
