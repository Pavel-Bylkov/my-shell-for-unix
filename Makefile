NAME		= minishell

LIBDIR		= ./libft/
LIBFT		= $(LIBDIR)libft.a
LIBFLAGS	= -L libft -lft -ltermcap

CFLAGS		= -Wall -Wextra -Werror
CC			= gcc -g

INCLUDES	= -I ./includes/. -I $(LIBDIR)includes/.

SRCDIR		= ./sources/
OBJDIR		= ./objs/

FLS			= \
			main \
			init_structs \
			mainloop \
			parser \
			str_split \
			termcap \
			termcap_keys \
			tools \
			history \
			errors \
			../ft_export_aam \
			../ft_minishell_aam \
			../ft_str_utils_aam \
			../ft_export_main_aam

SRC			= $(FLS)

OBJ			= $(addprefix $(OBJDIR), $(SRC:=.o))
DFLS		= $(SRC:=.d)

all: $(LIBFT) | $(NAME)

$(NAME):		$(LIBFT) $(OBJ)
	@echo '----Making minishell ------'
	@make		-C libft/
	$(CC)		$(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFLAGS) -o $(NAME)
	@echo "Ready"

$(OBJ):			$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p	$(OBJDIR)
	@$(CC)		$(CFLAGS) $(INCLUDES) -c $< -o $@ -MMD
	@echo "Compiled $@"

include $(wildcard $(addprefix $(OBJDIR), $(DFLS)))

tester:
	./tests/test_42fr.sh

$(LIBFT):
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
