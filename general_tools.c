/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:50:53 by amyburgh          #+#    #+#             */
/*   Updated: 2018/12/06 19:19:04 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const	t_dispatch	g_s[] = {
	{'%', T_PERC},
	{'s', T_STR},
	{'p', T_PTR},
	{'d', T_INT},
	{'i', T_INT},
	{'D', T_INT},
	{'f', T_FLOAT},
	{'F', T_FLOAT},
	{'o', T_OCTAL},
	{'u', T_UINT},
	{'U', T_UINT},
	{'x', T_HEX},
	{'X', T_HEX2},
	{'c', T_CHAR},
	{'C', T_WCHAR},
	{'\0', 0}
};

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

void	trim_string(char **str, size_t n, size_t *l)
{
	char	*temp;

	temp = *str;
	*str = ft_strndup(*str, n);
	*l = ft_strlen(*str);
	free(temp);
}

int		empty_input(t_pf p, char **str, uintmax_t n, size_t *l)
{
	if (p.m & T_STR && !*str)
		*str = ft_strdup("(null)");
	else if (p.m & T_CHAR && **str == '\0')
	{
		*l += 1;
		p.width ? p.width-- : 0;
		return (CNULL);
	}
	if (p.m >= T_INT && p.m <= T_HEX2 && p.m & POINT && !n)
	{
		free(*str);
		*str = ft_strnew(0);
	}
	return (0);
}
