/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:14:58 by whector           #+#    #+#             */
/*   Updated: 2021/06/29 13:21:25 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *b, int c, size_t len)
{
	unsigned char	*ptr;
	unsigned char	char_c;

	if ((b == NULL && len == 0))
		return (NULL);
	ptr = (unsigned char *)b;
	char_c = (unsigned char)c;
	while (len-- != 0)
	{
		if (*ptr == char_c)
			return (ptr);
		ptr++;
	}
	return (NULL);
}
