/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:11:16 by aamarei           #+#    #+#             */
/*   Updated: 2020/11/13 10:15:29 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*rez;

	if (s == NULL)
		return (NULL);
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	rez = str;
	if (start < ft_strlen(s))
	{
		while (s[start] && len-- != 0)
			*str++ = s[start++];
	}
	*str = '\0';
	return (rez);
}
