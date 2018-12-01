/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 21:16:20 by amyburgh          #+#    #+#             */
/*   Updated: 2018/11/25 21:17:25 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_strinsert(const char *insert, char **str)
{
	char	*new;
	size_t	len;
	size_t	i;
	size_t	j;

	len = *str ? ft_strlen(*str) : 0;
	len += insert ? ft_strlen(insert) : 0;
	if ((new = ft_strnew(len)))
	{
		i = 0;
		j = 0;
		if (str)
		{
			while ((*str)[j] && SPACES1((*str)[j]))
				new[i++] = (*str)[j++];
			if (insert)
				while (*insert)
					new[i++] = *insert++;
			while ((*str)[j])
				new[i++] = (*str)[j++];
		}
		free(*str);
		*str = new;
	}
}
