/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 11:09:36 by aamarei           #+#    #+#             */
/*   Updated: 2020/12/13 16:00:25 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	char	*s;
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (s1 != NULL && s1[i])
		i++;
	while (s2 != NULL && s2[k])
		k++;
	str = (char *)malloc(i + k + 1);
	if ((s = str) == NULL)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
		*s++ = s1[i++];
	i = 0;
	if (k > 0)
		while (s2[i])
			*s++ = s2[i++];
	*s = '\0';
	free(s1);
	return (str);
}

int			ft_in_set(char *str, char c)
{
	int		t;

	t = 1;
	if (str == NULL)
		return (0);
	while (str[t - 1] != c && str[t - 1] != '\0')
		t++;
	if (str[t - 1] == '\0')
		t = 0;
	return (t);
}

char		*ft_trim(char *str, int n)
{
	char	*rez;
	int		i;

	i = 0;
	while (str[n + i])
		i++;
	if (!(rez = (char *)malloc(i + 1)))
		return (NULL);
	i = 0;
	while (str[n + i])
	{
		rez[i] = str[n + i];
		i++;
	}
	rez[i] = '\0';
	free(str);
	return (rez);
}
