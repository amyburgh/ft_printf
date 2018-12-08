/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 23:32:34 by amyburgh          #+#    #+#             */
/*   Updated: 2018/12/07 18:43:46 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	old_format(t_pf *p)
{
	p->m |= L_L;
	if (p->m & L_HH)
		p->m ^= L_HH;
	if (p->m & L_H)
		p->m ^= L_H;
	if (p->m & L_LL)
		p->m ^= L_LL;
	if (p->m & L_J)
		p->m ^= L_J;
	if (p->m & L_Z)
		p->m ^= L_Z;
}

static void	get_specifier(t_pf *p, char **f)
{
	int		i;
	char	*temp;

	i = -1;
	while (g_s[++i].op)
	{
		if (g_s[i].op == **f)
		{
			p->m |= g_s[i].type;
			++*f;
			break ;
		}
	}
	if (ft_strchr("DUF", g_s[i].op))
		old_format(p);
	if (g_s[i].op == 'p')
		p->m |= POUND;
	else if (g_s[i].op == 'f' || g_s[i].op == 'F')
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
			break ;
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
		else if (**f == 'l' && *(*f + 1) == 'l')
			p->m |= L_LL;
		else if (**f == 'l' || **f == 'L')
			p->m |= L_L;
		else if (**f == 'j')
			p->m |= L_J;
		else if (**f == 'z')
			p->m |= L_Z;
		else
			break ;
		*f += (p->m & L_HH || p->m & L_LL ? 2 : 1);
	}
}

void		get_options(char **f, va_list ap, size_t *len)
{
	t_pf	p;

	p = (t_pf){0, 0, 0, 0};
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
	print_format(&p, ap, len);
}
