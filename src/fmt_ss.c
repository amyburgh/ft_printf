/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_ss.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 23:09:07 by amyburgh          #+#    #+#             */
/*   Updated: 2018/10/28 16:33:47 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	pf_wc_strlen(wchar_t *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// PROBABY NEED A MEMCOPY FOR WIDE CHARS HERE!

static void	padding(t_pf *p, wchar_t *str)
{
	char	*temp;
	char	*begin;
	size_t	b_len;
	size_t	b_new;

}

void	fmt_ss(t_pf	*p)
{
	wchar_t	*str;

	printf("\033[31Enter:\033[0m fmt_ss\n");
	printf("-------------------\n");

	if (p->masks & (PF_POUND | PF_ZERO | PF_PLUS | PF_SPACE))
		error(ERROR2);
//	if (!(str = va_arg(p->ap, wchar_t*)))
//		str = ft_strdup("(null)");
	p->len = pf_wc_strlen(str);
	if (p->masks & PF_PREC)
		p->len = MIN(p->len, p->prec);
	if (p->masks & PF_WIDTH)
		p->width = MAX(p->len, p->width);
	padding(p, str);
	p->format++;

//	printf("\033[34mstr: %s\n\033[0m", str);
	printf("--------------------\n");
	printf("\033[31mExit:\033[0m fmt_s\n");
}
