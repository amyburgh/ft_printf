/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:51:12 by amyburgh          #+#    #+#             */
/*   Updated: 2018/12/06 19:50:56 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>

static uintmax_t	overflow_signed(t_pf *p, uintmax_t n)
{
	if (p->m & L_H && ((intmax_t)n < SHRT_MIN || SHRT_MAX < (intmax_t)n))
		p->m ^= L_H;
	if (p->m & L_HH && ((intmax_t)n < CHAR_MIN || CHAR_MAX < (intmax_t)n))
		p->m ^= L_HH;
	if (p->m & L_L && ((intmax_t)n < LONG_MIN || LONG_MAX < (intmax_t)n))
	{
		p->m ^= L_L;
		p->m |= L_LL;
	}
	if (!(p->m & (L_H | L_HH | L_L | L_LL | L_J | L_Z)) && INT_MAX < n)
		p->m ^= L_L;
	if ((p->m & L_LL || p->m & L_J || p->m & L_Z) && LLONG_MAX < n)
	{
		p->overflow = 1;
		p->m ^= T_INT;
		p->m |= T_UINT;
	}
	return (n);
}

static uintmax_t	overflow_unsigned(t_pf *p, uintmax_t n)
{
	if (p->m & L_H && USHRT_MAX < n)
		p->m ^= L_H;
	if (p->m & L_HH && UCHAR_MAX < n)
		p->m ^= L_HH;
	if (!(p->m & (L_H | L_HH | L_L | L_LL | L_J | L_Z)) && UINT_MAX < n)
		p->m |= L_L;
	if (p->m & L_L && ULONG_MAX < n)
	{
		p->m ^= L_L;
		p->m |= L_LL;
	}
	return (n);
}

static uintmax_t	handle_signed(t_pf p, va_list ap, uintmax_t n)
{
	if (!(p.m & (L_H | L_HH | L_L | L_LL | L_J | L_Z)))
		n = va_arg(ap, int);
	else if (p.m & L_H)
		n = (short)va_arg(ap, int);
	else if (p.m & L_HH)
		n = (signed char)va_arg(ap, int);
	else if (p.m & L_L)
		n = va_arg(ap, long);
	else if (p.m & L_LL)
		n = va_arg(ap, long long);
	else if (p.m & L_J)
		n = va_arg(ap, intmax_t);
	else if (p.m & L_Z)
		n = va_arg(ap, ssize_t);
	return (n);
}

static uintmax_t	handle_unsigned(t_pf p, va_list ap, uintmax_t n)
{
	if (!(p.m & (L_H | L_HH | L_L | L_LL | L_J | L_Z)))
		n = va_arg(ap, unsigned int);
	else if (p.m & L_H)
		n = (unsigned short)va_arg(ap, int);
	else if (p.m & L_HH)
		n = (unsigned char)va_arg(ap, int);
	else if (p.m & L_L)
		n = va_arg(ap, unsigned long);
	else if (p.m & L_LL)
		n = va_arg(ap, unsigned long long);
	else if (p.m & L_J)
		n = va_arg(ap, uintmax_t);
	else if (p.m & L_Z)
		n = va_arg(ap, size_t);
	return (n);
}

uintmax_t			lenght_format(t_pf *p, va_list ap)
{
	uintmax_t	n;

	n = 0;
	if (p->m & T_INT)
	{
		n = handle_signed(*p, ap, n);
		n = overflow_signed(p, n);
	}
	else
	{
		n = handle_unsigned(*p, ap, n);
		n = overflow_unsigned(p, n);
	}
	return (n);
}
