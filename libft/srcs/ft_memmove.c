/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whector <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:15:47 by whector           #+#    #+#             */
/*   Updated: 2021/03/25 07:15:50 by whector          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptr;
	unsigned char	*srcp;

	if (src == dst)
		return (dst);
	ptr = (unsigned char *)dst;
	srcp = (unsigned char *)src;
	if ((dst == NULL && len == 0) || (dst == NULL && src == NULL))
		return (NULL);
	if ((size_t)srcp < (size_t)dst && (size_t)srcp + len >= (size_t)dst)
	{
		ptr = ptr + len - 1;
		srcp = srcp + len - 1;
		while (len-- != 0)
			*ptr-- = *srcp--;
		return (dst);
	}
	while (len-- != 0)
		*ptr++ = *srcp++;
	return (dst);
}
