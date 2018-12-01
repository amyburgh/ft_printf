/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcaseswap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 18:19:58 by amyburgh          #+#    #+#             */
/*   Updated: 2018/11/15 18:25:37 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcaseswap(char *str)
{
	int		i;
	char	mod;

	i = 0;
	mod = ' ';
	while (str[i])
	{
		if (IS_ALPHA(str[i]))
			str[i] ^= mod;
		i++;
	}
	return (str);
}
