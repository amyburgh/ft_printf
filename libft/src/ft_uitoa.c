/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 19:44:59 by amyburgh          #+#    #+#             */
/*   Updated: 2018/11/19 19:46:56 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macros.h"
#include "libft.h"

char	*ft_uitoa(unsigned int n)
{
	int		len;
	char	*str;

	if (!n)
		return (ft_strdup("0"));
	len = ft_digitcount(n);
	str = ft_strnew(len);
	if (!str)
		return (NULL);
	while (n)
	{
		str[--len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
