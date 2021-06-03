/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:30:47 by aamarei           #+#    #+#             */
/*   Updated: 2020/11/07 18:23:14 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*str;

	str = (char *)dst;
	if ((dst == NULL && n == 0) || (dst == NULL && src == NULL))
		return (NULL);
	while (n-- != 0)
		*str++ = *(char *)src++;
	return (dst);
}
