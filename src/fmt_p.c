/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_p.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 13:55:16 by amyburgh          #+#    #+#             */
/*   Updated: 2018/10/28 16:34:00 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	padding(t_pf	*p, char *str)
{

}

void	fmt_p(t_pf	*p)
{
	void	*ptr;

	if (p->masks & (PF_POUND | PF_ZERO | PF_PLUS | PF_SPACE))
		error(ERROR2);
	ptr = va_arg(p->ap, void *);
}
