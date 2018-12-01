/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 21:09:25 by amyburgh          #+#    #+#             */
/*   Updated: 2018/11/25 15:33:40 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_pow(long double n, int pow)
{
	while (pow--)
		n *= 10;
	return (n);
}

char	*ft_dtoa(long double n, int p)
{
	char	*s;
	char	*temp;

	s = ft_itoa(n);
	if (p && p > 0)
	{
		ft_strsuffix(&s, ".");
		n -= (int)n;
		n = ft_pow(n, p);
		temp = ft_itoa(n);
		ft_strsuffix(&s, temp);
		free(temp);
	}
	return (s);
}
