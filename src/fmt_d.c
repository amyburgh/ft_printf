/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 21:35:13 by amyburgh          #+#    #+#             */
/*   Updated: 2018/10/28 18:34:41 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t	get_format(t_pf *p)
{
	intmax_t	n;

	if (p->masks & PF_CHAR)
		n = va_arg(p->ap, int); // -> signed char
	else if (p->masks & PF_SHORT)
		n = va_arg(p->ap, int); // -> short int
	else if (p->masks & PF_LONG)
		n = va_arg(p->ap, int64_t);
	else if (p->masks & PF_LLONG)
		n = va_arg(p->ap, int64_t);
	else if (p->masks & PF_INTMAX)
		n = va_arg(p->ap, intmax_t);
	else if (p->masks & PF_SIZE_T)
		n = va_arg(p->ap, size_t);
	else
		n = va_arg(p->ap, int);
	p->sign = (n < 0 ? '-' : '+');
	if (p->sign == '-')
		p->masks |= PF_PLUS;
	return (ABS(n));
}

static void	padding(t_pf *p, char *str)
{
	char	*temp;
	char	*begin;
	size_t	b_len;
	size_t	b_new;

	b_len = (p->buffer ? pf_strlen(p->buffer) : 0);
	b_new = (p->masks & PF_WIDTH ? p->width : p->len);
	begin = (temp = pf_strnew(b_len + b_new));
	if (p->buffer)
		temp = pf_buffmemcpy(temp, p->buffer, b_len);
	if (p->masks & PF_PLUS)
		temp = pf_buffmemset(temp, p->sign, 1);
	if (p->masks & PF_MINUS)
		temp = pf_buffmemcpy(temp, str, p->len);
	if (p->width > p->len)
	{
		if (p->masks & PF_ZERO)
			temp = pf_buffmemset(temp, '0', b_new - p->len);
		else
			temp = pf_buffmemset(temp, ' ', b_new - p->len);
	}
	if (!(p->masks & PF_MINUS))
		temp = pf_buffmemcpy(temp, str, p->len);
	free(p->buffer);
	p->buffer = begin;
}

void	fmt_d(t_pf	*p)
{
//	intmax_t	n;
	char		*str;
	printf("\033[31mEnter:\033[0m fmt_d\n");
	printf("--------------------\n");

	if (p->masks & PF_POUND)
		error(ERROR2);
	str = pf_itoa(get_format(p)); //Might have to write a pf_atoi() with int64_t
	p->len = pf_strlen(str);
	if (p->masks & PF_PLUS)
		p->len++;
	if (p->masks & PF_PREC)
		p->len = MAX(p->len, p->prec);
	if (p->masks & PF_WIDTH)
		p->width = MAX(p->len, p->width);
	// MAYBE SOMETHING HERE
	padding(p, str);

	p->format++;printf("--------------------\n");
	printf("\033[31mExit:\033[0m fmt_d\n");
}
