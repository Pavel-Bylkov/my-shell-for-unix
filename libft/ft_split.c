/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:26:18 by aamarei           #+#    #+#             */
/*   Updated: 2020/11/13 18:50:01 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		num_words(char const *s, char c)
{
	int			i;
	int			num;

	i = 0;
	num = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			num++;
		i++;
	}
	return (num);
}

static void		clear_mas(char **str, int i)
{
	i--;
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

static void		find_word(char const *s, char c, int *t, int *len)
{
	*t = *t + *len;
	*len = 0;
	while (s[*t] == c)
		(*t)++;
	while (s[*t + *len] != c && s[*t + *len] != '\0')
		(*len)++;
}

char			**ft_split(char const *s, char c)
{
	char		**str;
	int			i;
	int			start;
	int			len;

	if (s == NULL)
		return (NULL);
	if (!(str = (char **)ft_calloc(sizeof(char *), (num_words(s, c) + 1))))
		return (NULL);
	i = 0;
	start = 0;
	len = 0;
	while (i < num_words(s, c))
	{
		find_word(s, c, &start, &len);
		if (!(str[i] = (char *)malloc(sizeof(char) * (len + 1))))
		{
			clear_mas(str, i);
			return (NULL);
		}
		ft_strlcpy(str[i], &s[start], len + 1);
		i++;
	}
	return (str);
}
