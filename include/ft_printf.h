/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 19:47:06 by amyburgh          #+#    #+#             */
/*   Updated: 2018/10/28 18:34:15 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdarg.h>
# include <stdlib.h>
# include "macros.h"

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

# define ERROR1 "\033[31merror:\033[0m incomplete format specifier\n"
# define ERROR2	"\033[31merror:\033[0m undefined behavior\n"
// warning: flag '0' results in undefined behavior with 's' conversion specifier [-Wformat]

/*
** ---------- Masks ----------
*/
// Flags
# define PF_POUND	(1 << 0)
# define PF_ZERO	(1 << 1)
# define PF_MINUS	(1 << 2)
# define PF_PLUS	(1 << 3)
# define PF_SPACE	(1 << 4)
# define PF_WILD	(1 << 5)

// Output
# define PF_CHAR	(1 << 6)
# define PF_SHORT	(1 << 7)
# define PF_LONG	(1 << 9)
# define PF_LLONG	(1 << 10)
# define PF_INTMAX	(1 << 11)
# define PF_SIZE_T	(1 << 12)
# define PF_DLONG	(1 << 13)

# define PF_WIDTH	(1 << 14)
# define PF_PREC	(1 << 15)
# define PF_LENGTH	(1 << 16)

typedef struct	s_pf
{
	int		fd;
	int		masks;
	int		width;
	int		prec;
	int		len;
	char	sign;
	va_list	ap;
	size_t	size;
	char	*format;
	char	*buffer;
}				t_pf;

typedef void	(*t_fmt)(t_pf*); //used to be -> int function
typedef struct	s_dispatch
{
	char 	op;
	t_fmt	s;
}				t_dispatch;
extern const	t_dispatch g_select[];

int		ft_printf(const char *str, ...);

/*
**	pf_functions
*/
void	error(char *str);

/*
** ---------- options.c ----------
*/
void	get_opts(t_pf *p);
/*
** ---------- tools.c ----------
*/
char	*pf_itoa(int n);
int		pf_atoi(const char *str);
size_t	pf_digitcount(long long n);
char	*pf_strchr(const char *s, int c);
char	*pf_strdup(const char *s1);
char	*pf_strccpy(char *dst, const char *src, char c);
char	*pf_strcpy(char *dst, const char *src);
void	pf_bzero(void *s, size_t n);
void	*pf_memalloc(size_t	size);
char	*pf_strnew(size_t size);
size_t	pf_strlen(const char *s);
void	pf_putstr(char const *s);
size_t	pf_formatlen(char *str);
void	print_masks(t_pf *p);
void	*pf_buffmemcpy(void *dst, const void *src, size_t n);
void	*pf_buffmemset(void *dst, int c, size_t n);
/*
** ---------- formats.c ----------
*/
void	fmt_s(t_pf *p);
void	fmt_ss(t_pf *p);
void	fmt_p(t_pf *p);
void	fmt_d(t_pf *p);
void	fmt_dd(t_pf *p);
void	fmt_o(t_pf *p);
void	fmt_oo(t_pf *p);
void	fmt_u(t_pf *p);
void	fmt_uu(t_pf *p);
void	fmt_x(t_pf *p);
void	fmt_xx(t_pf *p);
void	fmt_c(t_pf *p);
void	fmt_cc(t_pf *p);

void	fmt_e(t_pf *p);
void	fmt_ee(t_pf *p);
void	fmt_f(t_pf *p);
void	fmt_ff(t_pf *p);
void	fmt_g(t_pf *p);
void	fmt_gg(t_pf *p);
void	fmt_a(t_pf *p);
void	fmt_aa(t_pf *p);
void	fmt_n(t_pf *p);
void	fmt_percent(t_pf *p);

char	*pf_buffcat(char *s1, const char *s2, size_t *size);
void	print_time(char *str);
#endif
