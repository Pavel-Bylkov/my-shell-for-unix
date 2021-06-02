NAME = libft.a

CC       = gcc
CFLAGS   = -Wall -Wextra -Werror
OFLAGS   = -O2
DBGFLAGS = -g
INCLUDES = -I includes/
SRCDIR   = srcs/
OBJDIR   = objs/

FLS = \
        ft_atoi \
        ft_bzero \
        ft_calloc \
        ft_isalnum \
        ft_isalpha \
        ft_isascii \
        ft_isdigit \
        ft_isprint \
        ft_itoa \
        ft_memccpy \
        ft_memchr \
        ft_memcmp \
        ft_memcpy \
        ft_memmove \
        ft_memset \
        ft_putchar_fd \
        ft_putendl_fd \
        ft_putnbr_fd \
        ft_putstr_fd \
        ft_split \
        ft_strchr \
        ft_strdup \
        ft_strjoin \
        ft_strlcat \
        ft_strlcpy \
        ft_strlen \
        ft_strmapi \
        ft_strncmp \
        ft_strnstr \
        ft_strrchr \
        ft_strtrim \
        ft_substr \
        ft_tolower \
        ft_toupper \
		ft_lstadd_back \
		ft_lstadd_front \
		ft_lstclear \
		ft_lstdelone \
		ft_lstiter \
		ft_lstlast \
		ft_lstmap \
		ft_lstnew \
		ft_lstsize \
		get_next_line \
		get_next_line_utils

SRC      = $(FLS)

OBJ      = $(addprefix $(OBJDIR), $(SRC:=.o))
DFLS     = $(SRC:=.d)

override FLAGS ?= $(CFLAGS)

all: $(NAME)

# depends on object files only
$(NAME):		$(OBJ)
	@ar rc		$(NAME) $?
	@ranlib		$(NAME)
	@echo "Main functions added to $(NAME)"

$(OBJ):			$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p	$(OBJDIR)
	@$(CC)		$(FLAGS) $(INCLUDES) -c $< -o $@ -MMD
	@echo "Compiled $@"

debug:
	make FLAGS="$(CFLAGS) $(DBGFLAGS)" all

include $(wildcard $(addprefix $(OBJDIR), $(DFLS)))

clean:
	rm -rf		$(OBJDIR)

fclean:			clean
	rm -f		$(NAME)

re:				fclean all

.PHONY: all debug clean fclean re
