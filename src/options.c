/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:39:07 by amyburgh          #+#    #+#             */
/*   Updated: 2018/10/27 22:07:11 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	test_bits(t_pf *p)
{
	int i;

	i = 0;
	while (i < 32)
		p->masks |= 1 << i++;
}

void	get_flags(t_pf	*p)
{
	printf("Enter: get_flags! --> "); // Remove
	printf("%s\n", p->format);
	while (*p->format)
	{
		if (*p->format == '#')
			p->masks |= PF_POUND;
		else if (*p->format == '0')
			p->masks |= PF_ZERO;
		else if (*p->format == '-')
			p->masks |= PF_MINUS;
		else if (*p->format == '+')
			p->masks |= PF_PLUS;
		else if (*p->format == ' ')
			p->masks |= PF_SPACE;
		else if (*p->format == '*') // PADDING MASK!!!
			p->masks |= PF_WILD;
		else
			break;
		p->format++;
	}
}

void	get_width_prec(t_pf	*p)
{
	printf("Enter: get_width! --> "); // Remove
	printf("%s\n", p->format);
	if (IS_DIGIT(*p->format) || p->masks & PF_WILD)
	{
		p->masks |= PF_WIDTH; // Switch is already on for '*'
		p->width = (p->masks & PF_WILD ? va_arg(p->ap, int) : ft_atoi(p->format));
		p->format += (p->masks & PF_WILD ? 0 : ft_digitcount(p->width));
	}
	if (*p->format == '.')
	{
		p->masks |= PF_PREC;
		p->format++;
		if (IS_DIGIT(*p->format))
		{
			p->prec = ft_atoi(p->format);
			p->format += ft_digitcount(p->prec);
		}
		else if (*p->format == '*')
		{
			p->prec = va_arg(p->ap, int);
			p->format++;
		}
	}
}

void	get_length(t_pf	*p)
{
	printf("Enter: get_length!\n");
	while (1)
	{
		if (*p->format == 'h' && *(p->format + 1) != 'h')
			p->masks |= PF_SHORT;
		else if (*p->format == 'h' && *(p->format + 1) == 'h')
			p->masks |= PF_CHAR && p->format++;
		else if (*p->format == 'l' && *(p->format + 1) != 'l')
			p->masks |= PF_LONG;
		else if (*p->format == 'l' && *(p->format + 1) == 'l')
			p->masks |= PF_LLONG && p->format++;
		else if (*p->format == 'j')
			p->masks |= PF_INTMAX;
		else if (*p->format == 'z')
			p->masks |= PF_SIZE_T;
		else if (*p->format == 'L')
			p->masks |= PF_DLONG;
		else
			break ;
		p->format++;
	}
}

void	get_opts(t_pf *p)
{
	int i;
	int	mod;

	printf("Enter: get_opts!\n"); // Remove
	i = 0;
	mod = 0;
	p->masks = 0;
	p->width = 0;
	p->prec = 0;
	p->len = 0;
	get_flags(p);
	get_width_prec(p);
	get_length(p);
	print_masks(p); // Print switches
	while (i < 1) // 24... No. items in dispatch
	{
		if (*p->format == *ft_strchr("scdou", *p->format) && p->masks & PF_LONG)
			mod = ' ';
		if (g_select[i].op == (*p->format ^ mod))
			g_select[i].s(p);
		else if (i == 0) // CHANGE TO 24
			error(ERROR1);
		i++;
	}
}
