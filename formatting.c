/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:49:21 by amyburgh          #+#    #+#             */
/*   Updated: 2018/12/03 17:26:29 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	handle_pound(t_pf p, char **str, uintmax_t n)
{
	if (p.m & T_OCTAL && n)
		ft_strprefix("0", str);
	else if ((p.m & T_HEX && n) || p.m & T_PTR)
		ft_strprefix("0x", str);
	else if (p.m & T_HEX2 && n)
		ft_strprefix("0X", str);
	else if (p.m & T_OCTAL && p.m & POINT)
		ft_strprefix("0", str);
}

static void	apply_format(t_pf p, char **str, uintmax_t n)
{
	if (p.m & T_CHAR && !p.data.c && p.width)
		p.width--;
	if (p.m & POUND && !(p.m & ZERO))
		handle_pound(p, str, n);
	(intmax_t)n < 0 ? p.prec++ : 0;
	if (p.m & POINT && (size_t)p.prec > ft_strlen(*str) && ft_strlen(*str))
	{
		p.prec -= ft_strlen(*str);
		while (p.prec--)
			ft_strprefix("0", str);
	}
	if (p.m & SPACE && !(p.m & PLUS) && p.m & T_INT && (intmax_t)n >= 0)
		ft_strprefix(" ", str);
	//p.width -= ft_strlen(*str) + (p.m & PLUS ? 1 : 0) + (p.m & (POUND | ZERO) ? 2 : 1);
	p.width -= ft_strlen(*str) + (p.m & PLUS && (intmax_t)n >= 0 ? 1 : 0) + (p.m & POUND && p.m & ZERO ? 2 : 0);
	if (p.width > 0)
	{
		if (p.m & MINUS)
			while (p.width--)
				ft_strsuffix(str, " ");
		else
			while (p.width--)
				ft_strprefix(p.m & ZERO && !(p.m & POINT) ? "0" : " ", str);
	}
	if (p.m & POUND && p.m & ZERO)
		handle_pound(p, str, n);
	if (p.m & PLUS && (p.m & T_INT || p.m & T_FLOAT) && (intmax_t)n >= 0)
		ft_strinsert("+", str);
	if ((intmax_t)n < 0)
		handle_neg('-', '0', str);
	if (p.m & T_CHAR && !p.data.c && p.m & MINUS && ft_strlen(*str))
		handle_null(str);
}

static void	name_later(t_pf	p, char **str, uintmax_t n)
{
	if (p.m & T_CHAR || p.m & T_PERC)
		*str = ft_chartostr(p.data.c);
	else if (p.m & T_CHAR && !p.data.str)
		*str = ft_wchar_to_str('\0');
	else if (p.m & T_WCHAR)
		*str = ft_wchar_to_str(p.data.wc);
	else if (p.m & T_STR && !p.data.str)
		*str = ft_strdup("(null)");
	else if (p.m & T_STR)
		*str = ft_strndup(p.data.str, p.m & POINT ? p.prec : ft_strlen(p.data.str));
	else if (p.m & T_INT && !(p.m & POINT && !n && !p.prec))
		*str = ft_itoa_base(n, 10);
	else if (p.m & T_UINT && !(p.m & POINT && !n && !p.prec))
		*str = ft_uitoa_base(n, 10);
	else if (p.m & T_FLOAT & p.m & L_L && !(p.m & POINT && !n))
		*str = ft_dtoa(p.data2.ld, p.prec);
	else if (p.m & T_FLOAT && !(p.m & POINT && !n))
		*str = ft_dtoa(p.data2.d, p.prec);
	else if (p.m & T_HEX && !(p.m & POINT && !n))
		*str = ft_strcaseswap(ft_uitoa_base(n, 16));
	else if (p.m & T_HEX2 && !(p.m & POINT && !n))
		*str = ft_uitoa_base(n, 16);
	else if (p.m & T_PTR)
		*str = ft_itoa_base(p.data.p, 16);
	else if (p.m & T_OCTAL && !(p.m & POINT && !n))
		*str = ft_uitoa_base(n, 8);
	else
		*str = ft_strnew(0);
}

void	get_format(t_pf p, char **b, size_t *len)
{
	char		*str;
	uintmax_t	n;
	int			l;

	handle_errors(p);
	n = (p.m > T_STR && !(p.m & T_FLOAT) ? lenght_format(p) : 0);
	l = p.m & T_CHAR && !p.data.c ? p.width : 0;
	name_later(p, &str, n);
	if (p.m >= T_PERC)
	{
		apply_format(p, &str, n);
		if (p.m & T_CHAR && !p.data.c)
			*b = fill_buffer(b, *len, str, l);
		else
			*b = fill_buffer(b, *len, str, ft_strlen(str));
		*len += ft_strlen(str);
		if (p.m & T_CHAR && !p.data.c)
			*len += p.m & MINUS ? l : 1;
		free(str);
	}
}
