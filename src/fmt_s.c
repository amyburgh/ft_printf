/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_s.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 21:40:11 by amyburgh          #+#    #+#             */
/*   Updated: 2018/10/27 22:02:42 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	padding(t_pf	*p, char *str)
{
	char	*temp;
	char	*begin;
	size_t	b_len;
	size_t	b_new;

	b_len = (p->buffer ? ft_strlen(p->buffer) : 0);
	b_new = (p->masks & PF_WIDTH ? p->width : p->len);
	begin = (temp = ft_strnew(b_len + b_new));
	if (p->buffer)
		temp = pf_buffmemcpy(temp, p->buffer, b_len);
	if (p->masks & PF_MINUS)
		temp = pf_buffmemcpy(temp, str, p->len);
	if (p->width > p->len)
		temp = pf_buffmemset(temp, ' ', b_new - p->len);
	if (!(p->masks & PF_MINUS))
		temp = pf_buffmemcpy(temp, str, p->len);
	free(p->buffer);
	p->buffer = begin;
}

void	fmt_s(t_pf *p)
{
	char	*str;

	printf("\033[31mEnter:\033[0m fmt_s\n");
	printf("--------------------\n");

	if (p->masks & (PF_POUND | PF_ZERO | PF_PLUS | PF_SPACE))
		error(ERROR2);
	if (!(str = va_arg(p->ap, char*)))
		str = ft_strdup("(null)");
	p->len = ft_strlen(str);
	if (p->masks & PF_PREC) // LETTERS TO DISPLAY
		p->len = MIN(p->len, p->prec); // changed p->prec to p->len
	if (p->masks & PF_WIDTH) // PADDING
		p->width = MAX(p->len, p->width);
	padding(p, str);
	p->format++;
	p->size = ft_strlen(p->buffer);

	printf("\033[34mstr: %s\n\033[0m", str);
	printf("--------------------\n");
	printf("\033[31mExit:\033[0m fmt_s\n");
}
