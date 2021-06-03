/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 21:13:31 by aamarei           #+#    #+#             */
/*   Updated: 2020/11/06 16:53:07 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*rez;
	int		len;
	int		t;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	rez = (char *)malloc(len + 1);
	if (rez == NULL)
		return (NULL);
	if ((*f) == NULL)
		ft_strlcpy(rez, s, len);
	else
	{
		t = 0;
		while (s[t])
		{
			rez[t] = (*f)(t, s[t]);
			t++;
		}
		rez[t] = '\0';
	}
	return (rez);
}
