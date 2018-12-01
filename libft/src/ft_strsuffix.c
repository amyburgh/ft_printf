/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsuffix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:27:54 by amyburgh          #+#    #+#             */
/*   Updated: 2018/11/15 18:48:33 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_strsuffix(char **str, const char *suffix)
{
	char	*new;
	size_t	len;
	size_t	i;
	size_t	j;

	len = (*str ? ft_strlen(*str) : 0);
	len += (suffix ? ft_strlen(suffix) : 0);
	if ((new = ft_strnew(len)))
	{
		i = 0;
		if (str && *str)
			while ((*str)[i])
			{
				new[i] = (*str)[i];
				i++;
			}
		j = 0;
		if (suffix)
			while (*suffix)
				new[i + j++] = *suffix++;
		free(*str);
		*str = new;
	}
}
