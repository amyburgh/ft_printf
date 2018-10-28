/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 22:31:56 by amyburgh          #+#    #+#             */
/*   Updated: 2018/10/10 23:07:09 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>

int	main()
{
	char 	*str = "20#he+llo";
	uint8_t	flags;
	char 	*ping;
	int		i;

	ping = "#0-+ ";
	flags = 0;
/*	while (*str)
	{
		i = 0;
		while (ping[i])
		{
			if (*str == ping[i])
			{
				flags |= 1 << i;
				break;
			}
			i++;
		}
		str++;
	}*/
	while (*str)
	{
		if (*str == '#')
			flags |= 1 << 0;
		else if (*str == '0')
			flags |= 1 << 1;
		else if (*str == '-')
			flags |= 1 << 2;
		else if (*str == '+')
			flags |= 1 << 3;
		else if (*str == ' ')
			flags |= 1 << 4;
		else
			break;
		(str)++;
	}
	printf("%d\n", flags);
	return (0);
}
