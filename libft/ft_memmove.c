/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:02:51 by aamarei           #+#    #+#             */
/*   Updated: 2020/11/07 10:35:57 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void *src, size_t len)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	if ((dst == NULL && len == 0) || (dst == NULL && src == NULL))
		return (NULL);
	if (src < dst)
	{
		s1 = s1 + len - 1;
		s2 = s2 + len - 1;
		while (len-- > 0)
			*s1-- = *s2--;
		return (dst);
	}
	while (len-- > 0)
		*s1++ = *s2++;
	return (dst);
}
