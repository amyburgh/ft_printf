/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:49:21 by amyburgh          #+#    #+#             */
/*   Updated: 2018/12/06 19:15:50 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	handle_strings(t_pf p, char **str, size_t *l)
{
	p.m |= empty_input(p, str, 0, l);
	*l += ft_strlen(*str);
	if (p.m & POINT && (size_t)p.prec < *l && !(p.m & T_PERC))
		trim_string(str, p.prec, l);
	p.width -= *l;
	handle_width(p, str);
	if (p.m & CNULL)
		handle_null(str, p.m, l);
	else
		*l = ft_strlen(*str);
}

static void	handle_numbers(t_pf p, char **str, uintmax_t n, size_t *l)
{
	empty_input(p, str, n, l);
	*l = ft_strlen(*str);
	(intmax_t)n < 0 ? p.prec++ : 0;
	if (p.m & POINT && (size_t)p.prec > *l)
	{
		p.prec -= *l;
		while (p.prec--)
			ft_strprefix("0", str);
	}
	if (p.m & POUND && !(p.m & ZERO))
		handle_pound(p, str, n);
	if (p.m & SPACE && !(p.m & PLUS) && (intmax_t)n >= 0 && !(p.m & T_UINT))
		ft_strprefix(" ", str);
	*l = ft_strlen(*str) + (p.m & ZERO && p.m & POUND ? 2 : 0);
	p.width -= *l + (p.m & PLUS && (intmax_t)n >= 0 ? 1 : 0);
	handle_width(p, str);
	if (p.m & POUND && p.m & ZERO)
		handle_pound(p, str, n);
	if (p.m & PLUS && (intmax_t)n >= 0 && !(p.m & T_UINT))
		ft_strinsert("+", str);
	if (p.overflow)
		ft_strinsert("-", str);
	if ((intmax_t)n < 0)
		handle_neg('-', '0', str);
	*l = ft_strlen(*str);
}

static void	convert_strings(t_pf p, va_list ap, char **str)
{
	if (p.m & T_PERC)
		*str = ft_strdup("%");
	else if (p.m & T_CHAR)
		*str = ft_chartostr(va_arg(ap, int));
	else if (p.m & T_WCHAR)
		*str = ft_wchar_to_str(va_arg(ap, wchar_t));
	else if (p.m & T_STR)
		*str = ft_strdup(va_arg(ap, char*));
	else
		*str = ft_strnew(0);
}

static void	convert_numbers(t_pf p, va_list ap, char **str, uintmax_t n)
{
	if (p.m & T_INT)
		*str = ft_itoa_base(n, 10);
	else if (p.m & T_UINT)
		*str = ft_uitoa_base(n, 10);
//	else if (p.m & T_FLOAT && p.m & L_L)
//		*str = ft_dtoa(va_arg(ap, double), p.prec);
	else if (p.m & T_FLOAT)
		*str = ft_dtoa(va_arg(ap, double), p.prec);
	else if (p.m & T_HEX)
		*str = ft_strcaseswap(ft_uitoa_base(n, 16));
	else if (p.m & T_HEX2)
		*str = ft_uitoa_base(n, 16);
	else if (p.m & T_PTR)
		*str = ft_strcaseswap(ft_itoa_base(va_arg(ap, intptr_t), 16));
	else if (p.m & T_OCTAL)
		*str = ft_uitoa_base(n, 8);
	else
		*str = ft_strnew(0);
	//printf("%s\n", *str);
}

void		print_format(t_pf *p, va_list ap, size_t *len)
{
	char		*str;
	uintmax_t	n;
	size_t		l;

	l = 0;
	handle_errors(*p);
	n = (p->m >= T_INT && p->m < T_FLOAT ? lenght_format(p, ap) : 0);
	if (p->m < T_PTR)
	{
		convert_strings(*p, ap, &str);
		handle_strings(*p, &str, &l);
	}
	else
	{
		convert_numbers(*p, ap, &str, n);
		handle_numbers(*p, &str, n, &l);
	}
	write(1, str, l);
	free(str);
	*len += l;
}
