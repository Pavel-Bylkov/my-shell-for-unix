/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:53:56 by aamarei           #+#    #+#             */
/*   Updated: 2020/11/07 14:38:04 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*s;
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	if (s1 == NULL)
		return (NULL);
	while (s1[i])
		i++;
	if (s2 != NULL)
		while (s2[k])
			k++;
	i = k + i;
	str = (char *)malloc(i + 1);
	if ((s = str) == NULL)
		return (NULL);
	while (*s1)
		*str++ = *s1++;
	if (k > 0)
		while (*s2)
			*str++ = *s2++;
	*str = '\0';
	return (s);
}
