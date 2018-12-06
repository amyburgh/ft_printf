/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 19:50:21 by amyburgh          #+#    #+#             */
/*   Updated: 2018/12/06 00:08:01 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_size(uintmax_t new, int base)
{
	int i;

	i = 1;
	while (new > (uintmax_t)base - 1)
	{
		new /= base;
		i++;
	}
	return (i);
}

char		*ft_uitoa_base(uintmax_t value, int base)
{
	char		*str;
	uintmax_t	n;
	int			i;
	int			sign;

	if (base <= 1)
		return (NULL);
	n = value;
	sign = 0;
	i = ft_size(n, base);
	if (!(str = ft_strnew(i + sign)))
		return (NULL);
	while (i--)
	{
		str[i] = (char)(n % base + ((n % base > 9) ? 'A' - 10 : '0'));
		n /= base;
	}
	return (str);
}
