NAME		= minishell

LIBDIR		= ./libft/
LIB			= $(LIBDIR)libft.a
LIBFLAGS	= -ltermcap -L libft

CFLAGS		= -Wall -Wextra -Werror
CC			= gcc

INCLUDES	= -I includes/ -I $(LIBDIR)includes/

SRCDIR		= ./sources/
OBJDIR		= ./objs/

FLS			= \
			main \
			parser \
			termcap \
			tools \
			history \
			errors

SRC			= $(FLS)

OBJ			= $(addprefix $(OBJDIR), $(SRC:=.o))
DFLS		= $(SRC:=.d)

all: $(NAME)

$(NAME):		$(LIBFT) $(OBJ)
	@echo '----Making minishell ------'
	$(CC)		$(CFLAGS) $(OBJ) $(INCLUDES) $(LIBFLAGS) -o $(NAME)
	@echo "Ready"

$(OBJ):			$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p	$(OBJDIR)
	@$(CC)		$(CFLAGS) $(INCLUDES) -c $< -o $@ -MMD
	@echo "Compiled $@"

include $(wildcard $(addprefix $(OBJDIR), $(DFLS)))

tester:
	./tests/test_42fr.sh

$(LIBFT): libft_force_make
	@echo '---Making libft ------'
	@make		-C $(LIBDIR) --no-print-directory
	@echo 'Making libft done'

libft_clean:
	make clean	-C $(LIBDIR)

libft_fclean:
	make fclean	-C $(LIBDIR)

libft_re:
	make re		-C $(LIBDIR)

norma:
	norminette $(SRCDIR) $(LIBDIR)srcs/*.c $(LIBDIR)includes/*.h ./includes/

clean:
	rm -rf		$(OBJDIR)

fclean:			clean
	rm -f		$(NAME)

re:				fclean all

.PHONY: all debug clean fclean re