/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:32:35 by aamarei           #+#    #+#             */
/*   Updated: 2020/11/06 12:16:57 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	str1;
	unsigned char	str2;

	while (n-- != 0)
	{
		str1 = (unsigned char)*s1++;
		str2 = (unsigned char)*s2++;
		if (str1 != str2)
			return (str1 - str2);
		if (str1 == '\0' && str2 == '\0')
			return (0);
	}
	return (0);
}
