/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:08:10 by aamarei           #+#    #+#             */
/*   Updated: 2021/03/07 11:42:10 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int		in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char					*ft_strtrim(char const *s1, char const *set)
{
	int					i;
	unsigned int		len;
	char				*start;
	char				*end;
	char				*rez;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && in_set(s1[i], set))
		i++;
	start = (char *)&s1[i];
	if ((i = ft_strlen((char *)s1) - 1) != -1)
		while (i >= 0 && in_set(s1[i], set))
			i--;
	end = (char *)&s1[i];
	if (end == start)
		len = 2;
	else
		len = end - start + 2;
	if (!(rez = malloc(sizeof(char) * len)))
		return (NULL);
	rez[0] = '\0';
	ft_strlcpy(rez, start, len);
	return (rez);
}
