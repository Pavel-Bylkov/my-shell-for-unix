
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	32
# endif

int			get_next_line(int fd, char **line);
char		*gnl_strjoin(char *s1, char const *s2);
size_t		gnl_strlen(const char *s);
char		*gnl_str_endl(char *s);
char		*gnl_strdup(const char *str);

#endif
