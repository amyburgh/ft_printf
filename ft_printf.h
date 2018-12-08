/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 20:39:03 by amyburgh          #+#    #+#             */
/*   Updated: 2018/12/07 18:49:51 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stddef.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/include/libft.h"

/*
** ---------- Colors ----------
*/
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define PURPLE	"\033[35m"
# define CYAN	"\033[36m"
# define EOC	"\033[0m"

/*
** ---------- Error MSG ----------
*/
# define ERROR	"\033[31merror:\033[0m undefined behavior\n"

/*
** ---------- Masks ----------
*/
# define CNULL		(1 << 0)
# define POUND		(1 << 1)
# define ZERO		(1 << 2)
# define MINUS		(1 << 3)
# define PLUS		(1 << 4)
# define SPACE		(1 << 5)
# define WILD		(1 << 6)
# define POINT		(1 << 7)
# define L_HH		(1 << 8)
# define L_H		(1 << 9)
# define L_L		(1 << 10)
# define L_LL		(1 << 11)
# define L_J		(1 << 12)
# define L_Z		(1 << 13)
# define T_PERC		(1 << 14)
# define T_CHAR		(1 << 15)
# define T_WCHAR	(1 << 16)
# define T_STR		(1 << 17)
# define T_PTR		(1 << 18)
# define T_INT		(1 << 19)
# define T_UINT		(1 << 20)
# define T_OCTAL	(1 << 21)
# define T_HEX		(1 << 22)
# define T_HEX2		(1 << 23)
# define T_FLOAT	(1 << 24)

typedef struct	s_pf
{
	uint32_t	m;
	int			width;
	int			prec;
	int			overflow;
}				t_pf;

typedef struct	s_dispatch
{
	char	op;
	int		type;
}				t_dispatch;

extern const	t_dispatch g_s[];
int				ft_printf(char *str, ...);
/*
** ---------- get_format.c ----------
*/
void			get_options(char **f, va_list ap, size_t *len);
/*
** ---------- get_lenght.c ----------
*/
uintmax_t		lenght_format(t_pf *p, va_list ap);
/*
** ---------- print_format.c ----------
*/
void			print_format(t_pf *p, va_list ap, size_t *size);
/*
** ---------- format_tools.c ----------
*/
void			handle_pound(t_pf p, char **str, uintmax_t n);
void			handle_neg(char a, char b, char **str);
void			handle_null(char **str, int left, size_t *l);
void			handle_width(t_pf p, char **str);
void			handle_errors(t_pf p);
/*
** ---------- general_tools.c ----------
*/
size_t			get_num(char **f);
void			trim_string(char **str, size_t n, size_t *l);
int				empty_input(t_pf p, char **str, uintmax_t n, size_t *l);
#endif
