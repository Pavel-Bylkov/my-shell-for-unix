/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:49:28 by aamarei           #+#    #+#             */
/*   Updated: 2020/11/06 11:53:08 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char*)dst;
	if ((dst == NULL && n == 0) || (dst == NULL && src == NULL))
		return (NULL);
	while (n-- > 0)
	{
		*str++ = *(unsigned char *)src;
		if (*(unsigned char *)src == (unsigned char)c)
			return (str);
		src++;
	}
	return (NULL);
}
