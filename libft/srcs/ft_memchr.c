/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whector <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:14:58 by whector           #+#    #+#             */
/*   Updated: 2021/03/25 07:15:01 by whector          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *b, int c, size_t len)
{
	unsigned char	*ptr;
	unsigned char	char_c;

	if ((b == NULL && len == 0))
		return (NULL);
	ptr = (unsigned char*)b;
	char_c = (unsigned char)c;
	while (len-- != 0)
	{
		if (*ptr == char_c)
			return (ptr);
		ptr++;
	}
	return (NULL);
}
