/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 23:42:09 by amyburgh          #+#    #+#             */
/*   Updated: 2018/12/05 23:59:25 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_pound(t_pf p, char **str, uintmax_t n)
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

void	handle_neg(char a, char b, char **str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strchr(*str, a) && ft_strchr(*str, b))
	{
		while ((*str)[i] && (*str)[i] != a)
			i++;
		while ((*str)[j] && (*str)[j] != b)
			j++;
		if (i > j)
		{
			(*str)[j] = a;
			(*str)[i] = b;
		}
	}
}

void	handle_null(char **str, int left, size_t *l)
{
	size_t	i;

	i = 0;
	while ((*str)[i])
		i++;
	if (left & MINUS)
	{
		(*str)[i] = ' ';
		**str = '\0';
	}
	*l += i;
}

void	handle_width(t_pf p, char **str)
{
	if (p.width > 0)
	{
		if (p.m & MINUS && !(p.m & CNULL))
			while (p.width--)
				ft_strsuffix(str, " ");
		else
			while (p.width--)
				ft_strprefix(p.m & ZERO && !(p.m & POINT) ? "0" : " ", str);
	}
}

void	handle_errors(t_pf p)
{
	char	*error;

	error = NULL;
	if ((p.m & T_CHAR || p.m & T_WCHAR) &&
			(p.m & (POUND | ZERO | PLUS)))
		error = ERROR;
	else if (p.m & T_STR && (p.m & (POUND | ZERO | PLUS)))
		error = ERROR;
	else if (p.m & T_PTR && (p.m & (ZERO | PLUS | SPACE) || p.prec))
		error = ERROR;
	else if (p.m & T_INT && p.m & POUND)
		error = ERROR;
	else if (p.m & T_UINT && (p.m & (POUND)))
		error = ERROR;
	else if ((p.m & T_OCTAL || p.m & T_HEX || p.m & T_HEX2) &&
			(p.m & (SPACE | PLUS)))
		error = ERROR;
	if (error)
	{
		ft_putstr(error);
		exit(1);
	}
}
