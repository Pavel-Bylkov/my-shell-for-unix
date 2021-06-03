/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 22:25:58 by aamarei           #+#    #+#             */
/*   Updated: 2020/11/07 13:38:45 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned char	*str1;
	unsigned char	*str2;
	unsigned char	c;
	size_t			i;
	int				k;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	if (*haystack == '\0')
		return (NULL);
	while (*haystack++ != '\0' && i++ < len)
	{
		if (*(haystack - 1) == (c = (unsigned char)*needle))
		{
			str1 = (unsigned char *)(haystack - 1);
			str2 = (unsigned char *)needle;
			k = 0;
			while (*str1 == *str2 && *str1++ && *str2 && i - 1 + k++ <= len)
				str2++;
			if (*str2 == '\0')
				return ((char *)(haystack - 1));
		}
	}
	return (NULL);
}
