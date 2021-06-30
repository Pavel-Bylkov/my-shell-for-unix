/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whector <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:19:20 by whector           #+#    #+#             */
/*   Updated: 2021/03/25 07:19:22 by whector          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strcopy_fr(char **line, char *str)
{
	int k;

	ft_free((void **)line);
	k = ft_strlen(str);
	*line = (char *)malloc(sizeof(char) * k);
	k = 0;
	while (str[k] != '\0')
	{
		(*line)[k] = str[k];
		k++;
	}
	(*line)[k] = '\0';
}

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}

char	*ft_g_strdupanychr(char *str, char *end)
{
	char	*dst;
	int		len;

	len = 0;
	while (str[len] && (chr_in_str(str[len], end) == -1 ||
			quaote_is_open(str, len) != 0 
			|| backslash_is_active(str, len) != 0))
		len++;
	dst = ft_strdupn(str, len);
	return (dst);
}

char	*ft_g_strjoin(char *str1, int n, int k, char *str2)
{
	char	*res;
	char	*tmp;

	if (n == -1)
		str1[ft_strlen(str1) - 1] = '\0';
	if (k == 1)
	{
		tmp = str1;
		str1 = ft_strjoin(str1, "\n");
		ft_free((void **)&tmp);
	}
	res = ft_strjoin(str1, str2);
	ft_free((void **)&str1);
	ft_free((void **)&str2);
	return (res);
}
