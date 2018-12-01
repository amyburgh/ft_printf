/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strprefix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:15:39 by amyburgh          #+#    #+#             */
/*   Updated: 2018/11/15 20:08:54 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_strprefix(char const *prefix, char **str)
{
	char	*new;
	size_t	len;
	size_t	i;
	size_t	j;

	len = *str ? ft_strlen(*str) : 0;
	len += prefix ? ft_strlen(prefix) : 0;
	if ((new = ft_strnew(len)))
	{
		i = 0;
		if (prefix)
			while (*prefix)
				new[i++] = *prefix++;
		j = 0;
		if (str && *str)
			while ((*str)[j])
			{
				new[i + j] = (*str)[j];
				j++;
			}
		free(*str);
		*str = new;
	}
}
