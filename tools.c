/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:50:53 by amyburgh          #+#    #+#             */
/*   Updated: 2018/12/01 16:06:57 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*fill_buffer(char **buff, size_t len, const char *f, size_t i)
{
	char 	*new;

	if (!i)
		return (*buff);
	if ((new = ft_strnew(len + i)))
	{
		if (len)
			new = ft_memcpy(new, *buff, len);
		new = ft_memcpy(new + len, f, i);
		new -= len;
	}
	free(*buff);
	return (new);
}

void	handle_null(char **str)
{
	size_t	i;

	i = 0;
	while ((*str)[i])
		i++;
	(*str)[i] = ' ';
	**str = '\0';
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

void	handle_errors(t_pf p)
{
	char	*error;

	error = NULL;
	if ((p.m & T_CHAR || p.m & T_WCHAR) &&
			(p.m & (POUND | ZERO | PLUS)))
		error = ERROR;
	else if (p.m & T_STR && (p.m & (POUND | ZERO | PLUS)))
		error = ERROR;
	else if (p.m & T_PTR && (p.m & (POUND | ZERO | PLUS | SPACE) || p.prec))
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

size_t	get_num(char **f)
{
	size_t	n;

	n = 0;
	while (**f && IS_DIGIT(**f))
	{
		n *= 10;
		n += **f - '0';
		++*f;
	}
	return (n);
}

const t_dispatch	g_select[] = {
	{'%', T_PERC},
	{'s', T_STR},
//	{'s', T_WSTR}, // NEW
	{'p', T_PTR},
	{'d', T_INT},
	{'i', T_INT},
	{'D', T_INT}, // NEW
	{'f', T_FLOAT},
	{'o', T_OCTAL},
	{'u', T_UINT},
	{'U', T_UINT},
	{'x', T_HEX},
	{'X', T_HEX2},
	{'c', T_CHAR},
	{'C', T_WCHAR}, // NEW
	{'\0', 0}
};
