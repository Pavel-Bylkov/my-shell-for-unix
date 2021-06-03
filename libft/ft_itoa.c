/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:02:07 by aamarei           #+#    #+#             */
/*   Updated: 2020/11/07 15:23:02 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				ft_size_num(long long int n)
{
	long long int	k;
	int				t;

	k = n;
	t = 1;
	if (k <= 0)
		t = 2;
	while (k != 0)
	{
		k = k / 10;
		t++;
	}
	return (t);
}

static long long int	ft_new_num(long long int n)
{
	long long int	t;

	t = 0;
	if (n < 0)
		n = -1 * n;
	while (n != 0)
	{
		t = 10 * t + (n % 10);
		n = n / 10;
	}
	return (t);
}

char					*ft_itoa(int n)
{
	char			*str;
	int				t;
	int				t1;
	long long int	k;

	k = (long long int)n;
	t1 = ft_size_num(k);
	str = (char *)malloc(t1);
	if (str == NULL)
		return (NULL);
	t = 0;
	str[0] = '0';
	if (k < 0)
		str[t++] = '-';
	k = ft_new_num(k);
	while (t < t1 - 1)
	{
		str[t++] = (k % 10) + '0';
		k = k / 10;
	}
	str[t] = '\0';
	return (str);
}
