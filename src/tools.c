/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:31:07 by amyburgh          #+#    #+#             */
/*   Updated: 2018/10/27 22:03:34 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	pf_formatlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '%')
		i++;
	return (i);
}

void	*pf_memcpy(char *dst, char *src, size_t n) //Im I even using you?
{
	char	*str;

	str = dst;
	while (n--)
		*str++ = *src++;
	return (dst);
}

void	*pf_buffmemcpy(void	*dst, const void *src, size_t n)
{
	while (n--)
		*(char*)dst++ = *(const char*)src++;
	return (dst);
}

void	*pf_buffmemset(void	*dst, int c, size_t n)
{
	while (n--)
		*(unsigned char*)dst++ = (unsigned char)c;
	return (dst);
}

void	print_masks(t_pf *p) /* Stores 32 bit switches */
{
	long			n;
	unsigned int	s;
	unsigned int	value;

	n = 4294967296;
	s = 1;
	value = p->masks;
	printf("Masks: ");
	while (n >>= 1)
	{
		(value & n) ? printf("1") : printf("0");
		!(s++ % 4) ? printf(" ") : 0;
	}
	printf("\n");
}
