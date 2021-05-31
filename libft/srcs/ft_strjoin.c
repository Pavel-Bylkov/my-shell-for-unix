/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whector <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:18:27 by whector           #+#    #+#             */
/*   Updated: 2021/03/25 07:18:30 by whector          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	char	*tmp;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	res = (char *)malloc(len1 + len2 + 1);
	if (res == NULL)
		return (NULL);
	tmp = res;
	while (len1 != 0 && len1-- != 0)
		*tmp++ = *s1++;
	while (len2 != 0 && len2-- != 0)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (res);
}
