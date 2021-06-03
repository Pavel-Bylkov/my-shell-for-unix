/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:01:04 by aamarei           #+#    #+#             */
/*   Updated: 2020/11/08 12:53:13 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	char	*rez;
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	str = (char *)malloc(i + 1);
	if (str == NULL)
		return (NULL);
	rez = str;
	while (*s)
		*str++ = *(char *)s++;
	*str = *(char *)s;
	return (rez);
}
