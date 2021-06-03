/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 09:55:26 by aamarei           #+#    #+#             */
/*   Updated: 2020/11/08 12:41:47 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*c;
	size_t	i;

	c = (char *)malloc(nmemb * size);
	i = 0;
	if (c == NULL)
		return (NULL);
	while (i < nmemb * size)
		c[i++] = 0;
	return (c);
}
