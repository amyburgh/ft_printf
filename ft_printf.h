/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 20:39:03 by amyburgh          #+#    #+#             */
/*   Updated: 2018/11/30 15:12:00 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <unistd.h>
# include <stddef.h>
# include <stdarg.h>
# include <stdlib.h>
//# include "macros.h"
# include "libft/include/libft.h"
# include <stdio.h> // Remove later

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
// Flags
# define POUND		(1 << 0)
# define ZERO		(1 << 1)
# define MINUS		(1 << 2)
# define PLUS		(1 << 3)
# define SPACE		(1 << 4)
# define WILD		(1 << 5)
# define POINT		(1 << 6)

# define L_HH		(1 << 7)
# define L_H		(1 << 8)
# define L_L		(1 << 9)
# define L_LL		(1 << 10)
# define L_J		(1 << 11)
# define L_Z		(1 << 12)

# define T_PERC		(1 << 13)
# define T_CHAR		(1 << 14)
# define T_WCHAR	(1 << 15)
# define T_STR		(1 << 16)
//# define T_WSTR		(1 << 15)
# define T_PTR		(1 << 17)
# define T_INT		(1 << 18)
# define T_UINT		(1 << 19)
# define T_OCTAL	(1 << 20)
# define T_HEX		(1 << 21)
# define T_HEX2		(1 << 22)
# define T_FLOAT	(1 << 23) // NEW

typedef union			u_data
{
	char				c;
	unsigned char		uc;
	wchar_t				wc;
	short				s;
	unsigned short		us;
	int					i;
	unsigned int		ui;
	char				*str;
	wchar_t				*wstr;
	long				l;
	unsigned long		ul;
	long long			ll;
	unsigned long long	ull;
	intptr_t			p;
	size_t				s_t;
	ssize_t				us_t;
	intmax_t			im;
	uintmax_t			uim;
	double				d; // NEW
	long double			ld;
}						t_data;

typedef struct	s_pf
{
	t_data	data;
	uint32_t m;
	int		width;
	int		prec;
}				t_pf;

typedef struct	s_dispatch
{
	char 	op;
	int		type;
}				t_dispatch;

extern const	t_dispatch g_select[];

int		ft_printf(char *str, ...);

/*
** ---------- lenght.c ----------
*/
uintmax_t	lenght_format(t_pf p);
/*
** ---------- formatting.c ----------
*/
void	get_format(t_pf p, char **b, size_t *size); //added b
/*
** ---------- tools.c ----------
*/
void	handle_null(char **str);
void	handle_neg(char a, char b, char **str);
void	ft_strinsert(const char *insert, char **str);
char	*fill_buffer(char **buff, size_t len, const char *f, size_t i);
void	handle_errors(t_pf p);
void	print_char(char c, size_t *size);
size_t	get_num(char **f);
/*
** ---------- formats.c ----------
*/
void	print_union(t_pf p);
#endif
