/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:16:12 by aamarei           #+#    #+#             */
/*   Updated: 2021/06/30 17:23:16 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2);
int		ft_in_set(char *str, char c);
char	*ft_trim(char *str, int n);
int		ft_gnl_work(int fd, char **line, char **remainder);
int		get_next_line(int fd, char **line);

#endif
