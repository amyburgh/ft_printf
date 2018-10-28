/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 16:32:29 by amyburgh          #+#    #+#             */
/*   Updated: 2018/10/27 22:16:25 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "ft_printf.h"

void	error(char *str)
{
	ft_putstr(str);
	exit (1);
}

void	fill_buffer(t_pf *p)
{
	char 	*temp;
	char 	*begin;
	size_t	n;
	size_t	len;

	len = pf_formatlen(p->format);
	n = 0;
	if (p->buffer)
		n = ft_strlen(p->buffer);
	temp = ft_strnew(n + len);
	begin = temp;
	if (p->buffer)
	{
		ft_strcpy(temp, p->buffer); // Use memcopy
		temp += n; //PROBLEM!!!!!!!!!!!!!!
	}
	ft_strccpy(temp, p->format, '%');
	p->format += len; // Find better way!
	free(p->buffer);
	p->buffer = begin;
}

int		ft_printf(const char *format, ...)
{
	t_pf	p;

	p.fd = 1;
	p.format = (char*)format;
	p.buffer = NULL;
	p.size = 0;
	va_start(p.ap, format);
	while (*p.format)
	{
		if (*p.format == '%')
			*p.format++ ? get_opts(&p) : error(ERROR1);
		else
			fill_buffer(&p);
	}
	va_end(p.ap);
	p.size = ft_strlen(p.buffer); // Review this logic!
	printf("++++++++++++++++++++++++++++++++++++++++++++++++\n");
	write(p.fd, p.buffer, p.size);
	return ((int)p.size);
}
