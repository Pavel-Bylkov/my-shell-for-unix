NAME = minishell
LIBDIR = ./libft
LIB = $(LIBDIR)libft.a

CFLAGS = -Wall -Wextra -Werror
CC = gcc

INCLUDES = ./includes/
INCLUDES_LIB = ./libft/includes/

OBJ_DIR = ./objs/

tester:
	./tests/test_42fr.sh