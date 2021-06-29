/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:15:40 by whector           #+#    #+#             */
/*   Updated: 2021/06/29 13:05:26 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_number(const char *str)
{
	int	n;

	n = 0;
	while (str[n] >= '0' && str[n] <= '9')
		n++;
	return (n);
}

static int	check_sign(const char *str, int *i)
{
	int	flag;

	flag = 1;
	if (str[*i] == '+')
		*i = *i + 1;
	else if (str[*i] == '-')
	{
		flag = -flag;
		*i = *i + 1;
	}
	return (flag);
}

int	ft_atoi(const char *nptr)
{
	int					i;
	int					flag;
	unsigned long int	res;
	int					n;

	i = 0;
	res = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\f'
		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	flag = check_sign(nptr, &i);
	n = len_number(&nptr[i]);
	if (n > 18 && flag == 1)
		return (-1);
	if (n > 18 && flag == -1)
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res + nptr[i++] - 48;
		res *= 10;
	}
	res = res / 10;
	return ((flag < 0) * -res + (flag >= 0) * res);
}
