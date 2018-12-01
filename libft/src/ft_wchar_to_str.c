/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar_to_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 18:07:20 by amyburgh          #+#    #+#             */
/*   Updated: 2018/11/13 20:49:23 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_wchar_to_str(wchar_t wc)
{
	char	*str;

	str = ft_strnew(sizeof(wchar_t));
	*((wchar_t*)str) = wc;
	return (str);
}
