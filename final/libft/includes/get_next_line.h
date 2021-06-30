/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whector <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:19:20 by whector           #+#    #+#             */
/*   Updated: 2021/03/25 07:19:22 by whector          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	32
# endif

typedef struct		s_rl_my
{
	char		*arr;
	char		*buf;
	char		*p_n;
	char		*tmp;
}					t_rl_my;

int			get_next_line(int fd, char **line);
char		*gnl_strjoin(char *s1, char const *s2);
size_t		gnl_strlen(const char *s);
char		*gnl_str_endl(char *s);
char		*gnl_strdup(const char *str);

#endif
