/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 21:09:25 by amyburgh          #+#    #+#             */
/*   Updated: 2018/12/06 19:40:04 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_pow(long double n, int pow, size_t *mod)
{
	while (pow--)
	{
		n *= 10;
		if (!((int)n))
			++*mod;
	}
	return (n);
}

char		*ft_dtoa(long double n, int p)
{
	char	*s;
	char	*temp;
	size_t	mod;

	s = ft_itoa(n);
	mod = 0;
	if (p && p > 0)
	{
		ft_strsuffix(&s, ".");
		n -= (int)n;
		n = ft_pow(n, p, &mod);
		p -= mod;
		while (mod--)
			ft_strsuffix(&s, "0");
		if (n)
		{
			temp = ft_itoa(n);
			ft_strsuffix(&s, temp);
			free(temp);
		}
		else
			while (p--)
				ft_strsuffix(&s, "0");
	}
	return (s);
}
