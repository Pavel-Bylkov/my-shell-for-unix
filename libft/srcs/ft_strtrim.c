/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whector <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:20:48 by whector           #+#    #+#             */
/*   Updated: 2021/03/25 07:20:51 by whector          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_ptr_start(char const *s, char const *set)
{
	char	*ptr;
	char	*str;
	char	*set_del;
	int		flag;

	str = (char *)s;
	ptr = NULL;
	flag = 1;
	while (*str && flag)
	{
		set_del = (char *)set;
		flag = 0;
		while (*set_del && flag == 0)
		{
			if (*str == *set_del++)
			{
				ptr = str + 1;
				flag = 1;
			}
		}
		str++;
	}
	if (ptr == NULL)
		ptr = (char *)s;
	return (ptr);
}

static char	*ft_ptr_end(char *s, char const *set)
{
	size_t	i;
	char	*ptr;
	size_t	n;
	int		flag;

	i = 0;
	while (s[i])
		i++;
	ptr = &s[i];
	flag = 1;
	while (--i != 0 && flag)
	{
		n = 0;
		flag = 0;
		while (set[n] && flag == 0)
		{
			if (set[n++] == s[i])
			{
				ptr = &s[i];
				flag = 1;
			}
		}
	}
	return (ptr);
}

static char	*ft_strtrim_2(char const *s1, char const *set)
{
	char	*res;
	char	*tmp;
	char	*tmp_cpy;
	char	*tmp_end;
	size_t	len;

	tmp_cpy = ft_ptr_start(s1, set);
	tmp_end = (*tmp_cpy == '\0') ? tmp_cpy : ft_ptr_end(tmp_cpy, set);
	len = (size_t)tmp_end - (size_t)tmp_cpy + 1;
	res = (char *)malloc(len);
	if (res == NULL)
		return (NULL);
	tmp = res;
	while ((size_t)tmp_cpy != (size_t)tmp_end)
		*tmp++ = *tmp_cpy++;
	*tmp = '\0';
	return (res);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*res;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (set[0] == '\0' || s1[0] == '\0')
		res = ft_strdup(s1);
	else
		res = ft_strtrim_2(s1, set);
	return (res);
}
