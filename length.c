/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:51:12 by amyburgh          #+#    #+#             */
/*   Updated: 2018/11/30 12:52:21 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static uintmax_t	handle_signed(t_pf p, uintmax_t n)
{
		if (!(p.m & (L_HH | L_H | L_L | L_LL | L_J | L_Z)))
			n = p.data.i;
		else if (p.m & L_HH)
			n = p.data.c;
		else if (p.m & L_H)
			n = p.data.s;
		else if (p.m & L_L)
			n = p.data.l;
		else if (p.m & L_LL)
			n = p.data.ll;
		else if (p.m & L_J)
			n = p.data.im;
		else if (p.m & L_Z)
			n = p.data.s_t;
		return (n);
}

static uintmax_t	handle_unsigned(t_pf p, uintmax_t n)
{
		if (!(p.m & (L_HH | L_H | L_L | L_LL | L_J | L_Z)))
			n = p.data.ui;
		else if (p.m & L_HH)
			n = p.data.uc;
		else if (p.m & L_H)
			n = p.data.us;
		else if (p.m & L_L)
			n = p.data.ul;
		else if (p.m & L_LL)
			n = p.data.ull;
		else if (p.m & L_J)
			n = p.data.uim;
		else if (p.m & L_Z)
			n = p.data.s_t;
		return (n);
}

uintmax_t	lenght_format(t_pf p)
{
	uintmax_t	n;

	n = 0;
	if (p.m & T_INT)
		n = handle_signed(p, n);
	else
		n = handle_unsigned(p, n);
	return(n);
}
