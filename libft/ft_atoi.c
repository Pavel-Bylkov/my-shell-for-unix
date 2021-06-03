/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 09:33:31 by aamarei           #+#    #+#             */
/*   Updated: 2020/11/07 13:57:16 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sign(char *str)
{
	if (*str == '-')
		return (-1);
	return (1);
}

int			ft_atoi(const char *nptr)
{
	char	*str;
	int		k;
	int		z;
	int		i;

	k = 0;
	z = 1;
	i = 1;
	str = (char *)nptr;
	while (*str == ' ' || *str == '\t' || *str == '\v' || *str == '\n' ||
			*str == '\r' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
		z = sign(str++);
	while (*str >= '0' && *str <= '9')
	{
		k = k * 10 + *str - '0';
		str++;
		i++;
	}
	k = z * k;
	if (i > 18)
		k = (z == -1) ? 0 : -1;
	return (k);
}
