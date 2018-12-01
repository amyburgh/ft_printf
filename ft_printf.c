/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 20:49:41 by amyburgh          #+#    #+#             */
/*   Updated: 2018/12/01 00:04:13 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_specifier(t_pf *p, char **f)
{
	int		i;
	char	*temp;

	i = 0;
	while (g_select[i].op)
	{
		if (g_select[i].op == **f)
		{
			p->m |= g_select[i].type;
			++*f;
			break;
		}
		i++;
	}
	if (g_select[i].op == '%')
	{
		p->data = (t_data)'%';
		p->m |= T_PERC;
	}
	if (g_select[i].op == 'f')
	{
		temp = *f;
		while (*temp != '%' && *temp != '.')
			--temp;
		if (*temp == '%')
			p->prec = 6;
	}
}

static void	get_flags(t_pf *p, char **f)
{
	while (**f)
	{
		if (**f == '#')
			p->m |= POUND;
		else if (**f == '0')
			p->m |= ZERO;
		else if (**f == '-')
			p->m |= MINUS;
		else if (**f == '+')
			p->m |= PLUS;
		else if (**f == ' ')
			p->m |= SPACE;
		else if (**f == '*')
			p->m |= WILD;
		else
			break;
		++*f;
	}
}

static void	get_length(t_pf *p, char **f)
{
	while (**f)
	{
		if (**f == 'h' && *(*f + 1) == 'h')
			p->m |= L_HH;
		else if (**f == 'h')
			p->m |= L_H;
		else if (**f == 'l' && *(*f + 1) =='l')
			p->m |= L_LL;
		else if (**f == 'l' || **f == 'L')
			p->m |= L_L;
		else if (**f == 'j')
			p->m |= L_J;
		else if (**f == 'z')
			p->m |= L_Z;
		else
			break;
		*f += (p->m & L_HH || p->m & L_LL ? 2 : 1);
	}
}

static void	get_options(char **f, char **b, va_list ap, size_t *len)
{
	t_pf	p;

	p = (t_pf){{0}, 0, 0, 0};
	get_flags(&p, f);
	p.width = p.m & WILD ? va_arg(ap, int) : get_num(f);
	if (**f == '.')
	{
		p.m |= POINT;
		++*f;
		if (**f == '*')
		{
			++*f;
			p.prec = va_arg(ap, int);
		}
		else
			p.prec = get_num(f);
	}
	get_length(&p, f);
	get_specifier(&p, f);
	if (p.m & T_FLOAT && p.m & L_L)
		p.data.ld = va_arg(ap, long double);
	else if (p.m & T_FLOAT)
		p.data.d = va_arg(ap, double);
	else if (!(p.m & T_PERC))
		p.data = va_arg(ap, t_data);
	get_format(p, b, len);
}

static void	parse_format(char *f, char **b, va_list ap, size_t *len)
{
	size_t	i;

	i = 0;
	while (f[i])
	{
		if (f[i] == '%')
		{
			*b = fill_buffer(b, *len, f, i);
			f += i + 1;
			*len += i;
			get_options(&f, b, ap, len);
			i = 0;
		}
		else
			i++;
	}
	*b = fill_buffer(b, *len, f, i);
	*len += i;
}

int		ft_printf(char *format, ...)
{
	va_list	ap;
	size_t	len;
	char	*buffer;

	if (format)
	{
		len = 0;
		buffer = ft_strnew(0);
		va_start(ap, format);
		parse_format(format, &buffer, ap, &len);
		va_end(ap);
		write(1, buffer, len);
		free(buffer);
		return (len);
	}
	return (0);
}
