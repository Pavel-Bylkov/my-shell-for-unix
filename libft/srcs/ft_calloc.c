/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:16:24 by whector           #+#    #+#             */
/*   Updated: 2021/06/29 13:06:37 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	unsigned char	*ptr;
	size_t			len;

	len = number * size;
	ptr = (unsigned char *)malloc(len);
	if (NULL == ptr)
		return (NULL);
	ft_bzero(ptr, len);
	return ((void *)ptr);
}
