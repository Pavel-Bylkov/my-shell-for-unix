/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:09:24 by aamarei           #+#    #+#             */
/*   Updated: 2020/11/07 16:20:18 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			s[15];
	long long int	t;
	int				k;

	t = (long long int)n;
	if (t < 0)
		t = -1 * t;
	k = 0;
	s[0] = 0 + '0';
	while (t != 0)
	{
		s[k++] = (t % 10) + '0';
		t = t / 10;
	}
	if (n < 0)
		s[k++] = '-';
	if (k == 0)
		k++;
	while (k != 0)
	{
		write(fd, &s[k - 1], 1);
		k--;
	}
}
