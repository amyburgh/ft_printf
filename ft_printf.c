/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 20:49:41 by amyburgh          #+#    #+#             */
/*   Updated: 2018/12/06 00:27:42 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_format(char *f, va_list ap, size_t *len)
{
	size_t	i;

	i = 0;
	while (f[i])
	{
		if (f[i] == '%')
		{
			write(1, f, i);
			f += i + 1;
			*len += i;
			get_options(&f, ap, len);
			i = 0;
		}
		else
			i++;
	}
	write(1, f, i);
	*len += i;
}

int			ft_printf(char *format, ...)
{
	va_list	ap;
	size_t	len;

	len = 0;
	if (format)
	{
		va_start(ap, format);
		parse_format(format, ap, &len);
		va_end(ap);
	}
	return (len);
}
