/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whector <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:21:01 by whector           #+#    #+#             */
/*   Updated: 2021/03/25 07:21:03 by whector          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	char	*tmp;

	if (s == NULL)
		return (NULL);
	res = (char *)malloc(len + 1);
	if (res == NULL)
		return (NULL);
	if (start < ft_strlen((char *)s))
	{
		tmp = res;
		while (s[start] && len-- != 0)
			*tmp++ = s[start++];
		*tmp = '\0';
	}
	else
		res[0] = '\0';
	return (res);
}
