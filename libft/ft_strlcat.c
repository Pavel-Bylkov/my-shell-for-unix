/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 21:07:15 by aamarei           #+#    #+#             */
/*   Updated: 2020/11/07 12:06:09 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	size_dst;
	size_t	size_src;
	size_t	i;
	size_t	n;

	size_dst = ft_strlen(dst);
	size_src = ft_strlen(src);
	n = size_dst;
	i = 0;
	if (size_dst < (dstsize - 1) && dstsize > 0)
	{
		while (src[i] && size_dst + i < (dstsize - 1))
			dst[n++] = src[i++];
		dst[n] = 0;
	}
	if (dstsize <= size_dst)
		size_dst = dstsize;
	return (size_dst + size_src);
}
