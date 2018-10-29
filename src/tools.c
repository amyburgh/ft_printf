/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:31:07 by amyburgh          #+#    #+#             */
/*   Updated: 2018/10/28 18:33:43 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

char	*pf_itoa(int n)
{
	int		len;
	char	*str;

	if (!n)
		return (pf_strdup("0"));
	if (n == INT_MIN)
		return (pf_strdup(INT_MIN_STR));
	len = pf_digitcount(n);
	len = IS_NEG(n) ? len + 1 : len;
	str = pf_strnew(len);
	if (!str)
		return (NULL);
	if (IS_NEG(n))
	{
		str[0] = '-';
		n = ABS(n);
	}
	while (n)
	{
		str[--len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

int	pf_atoi(const char *str)
{
	long long	nb;
	int			flag;

	nb = 0;
	flag = 1;
	while (ALLSPACES(*str))
		str++;
	flag = (*str == '-') ? -1 : 1;
	str = (*str == '+' || *str == '-') ? str + 1 : str;
	while (IS_DIGIT(*str))
		nb = nb * 10 + (*str++ - 48);
	return ((int)(nb * flag));
}

size_t	pf_digitcount(long long n)
{
	if (n == 0)
		return (0);
	return (1 + pf_digitcount(n / 10));
}

char	*pf_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	if (!c && !s[i])
		return ((char *)s + i);
	return (NULL);
}

char	*pf_strdup(const char *s1)
{
	char	*str_dup;
	char	*begin;

	str_dup = (char *)malloc(sizeof(*str_dup) * (pf_strlen(s1) + 1));
	if (!str_dup)
		return (NULL);
	begin = str_dup;
	while (*s1)
		*str_dup++ = *s1++;
	*str_dup = '\0';
	return (begin);
}

char	*pf_strccpy(char *dst, const char *src, char c)
{
	int	i;

	i = -1;
	while (src[++i] && (src[i] != c))
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

char	*pf_strcpy(char *dst, const char *src)
{
	char	*str;

	str = dst;
	while (*src)
		*str++ = *src++;
	*str = '\0';
	return (dst);
}

void	pf_bzero(void *s, size_t n)
{
	while (n--)
		*(unsigned char*)s++ = 0;
}

void	*pf_memalloc(size_t size)
{
	void	*fresh;

	fresh = (void *)malloc(size);
	if (!fresh)
		return (NULL);
	pf_bzero(fresh, size);
	return (fresh);
}

char	*pf_strnew(size_t size)
{
	return ((char *)pf_memalloc(size + 1));
}

size_t	pf_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	pf_putstr(char const *s)
{
	if (s)
		write(1, s, pf_strlen(s));
}

size_t	pf_formatlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '%')
		i++;
	return (i);
}

void	*pf_memcpy(char *dst, char *src, size_t n) //Im I even using you?
{
	char	*str;

	str = dst;
	while (n--)
		*str++ = *src++;
	return (dst);
}

void	*pf_buffmemcpy(void	*dst, const void *src, size_t n)
{
	while (n--)
		*(char*)dst++ = *(const char*)src++;
	return (dst);
}

void	*pf_buffmemset(void	*dst, int c, size_t n)
{
	while (n--)
		*(unsigned char*)dst++ = (unsigned char)c;
	return (dst);
}

void	print_masks(t_pf *p) /* Stores 32 bit switches */
{
	long			n;
	unsigned int	s;
	unsigned int	value;

	n = 4294967296;
	s = 1;
	value = p->masks;
	printf("Masks: ");
	while (n >>= 1)
	{
		(value & n) ? printf("1") : printf("0");
		!(s++ % 4) ? printf(" ") : 0;
	}
	printf("\n");
}
