/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:17:38 by whector           #+#    #+#             */
/*   Updated: 2021/06/29 13:27:58 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strdupchr(char *s, char c)
{
	char	*res;
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	res = (char *)malloc(i + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s[i] != c && s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static void	free_strs(char **res)
{
	size_t	i;

	i = 0;
	while (res[i] != NULL)
	{
		free(res[i]);
		res[i] = NULL;
		i++;
	}
	free(res);
	res = NULL;
}

static size_t	get_nstrs(char *str, char c)
{
	size_t	n_strs;

	n_strs = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
			n_strs++;
		while (*str && *str != c)
			str++;
	}
	return (n_strs);
}

static void	ft_strscpy(char **res, size_t n, char *str, char c)
{
	size_t	i;

	i = 0;
	while (*str && i < n)
	{
		while (*str && *str == c)
			str++;
		res[i] = ft_strdupchr(str, c);
		if (res[i++] == NULL)
		{
			free_strs(res);
			return ;
		}
		while (*str != c && *str)
			str++;
	}
	res[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	*str;
	char	**res;
	size_t	nstrs;

	if (s == NULL)
		return (NULL);
	str = (char *)s;
	nstrs = get_nstrs(str, c);
	res = (char **)malloc(sizeof(char *) * (nstrs + 1));
	if (res == NULL)
		return (NULL);
	ft_strscpy(res, nstrs, str, c);
	return (res);
}
