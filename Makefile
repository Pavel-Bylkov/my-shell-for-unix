NAME		= minishell

LIBDIR		= ./libft/
LIBFT		= $(LIBDIR)libft.a
LIBFLAGS	= -L libft -lft -lreadline -L/Users/aamarei/.brew/opt/readline/lib #-ltermcap

CFLAGS		= -Wall -Wextra -Werror -D DEBUG=1
CC			= gcc -g

INCLUDES	= -I ./includes/. -I $(LIBDIR)includes/. -I/Users/aamarei/.brew/opt/readline/include

SRCDIR		= ./sources/
OBJDIR		= ./objs/

FLS			= \
			main \
			init_structs \
			mainloop \
			parser \
			str_split \
			termcap \
			tools \
			errors \
			../ft_minishell_pipe_aam \
			../ft_str_utils_aam \
			../ft_export_main_aam \
			../ft_export_aam \
			../ft_unset_main_aam \
			../ft_unset_aam \
			../ft_env_main_aam \
			../ft_exit_main_aam \
			../ft_pwd_main_aam \
			../ft_cd_main_aam \
			../ft_cd_aam \
			../ft_echo_main_aam \
			../ft_output_err_aam \
			../ft_cd_path_aam \
			../ft_minishell_main_aam \
			../ft_minishell_init_aam \
			../ft_minishell_choice_aam \
			../ft_minishell_utils_aam \
			../ft_minishell_build_aam

SRC			= $(FLS)

OBJ			= $(addprefix $(OBJDIR), $(SRC:=.o))
DFLS		= $(SRC:=.d)

all: $(LIBFT) | $(NAME)

$(NAME):		$(LIBFT) $(OBJ)
	@echo '----Making minishell ------'
	#@make		-C libft/
	$(CC)		$(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFLAGS) -o $(NAME)
	@echo "Ready"

$(OBJ):			$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p	$(OBJDIR)
	@$(CC)		$(CFLAGS) $(INCLUDES) -c $< -o $@ -MMD
	@echo "Compiled $@"


bonus: all

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
	rm -rf		$(OBJDIR) *.o *.d

fclean:			clean
	rm -f		$(NAME)
	rm -rf		.*.tmp *.tmp

re:				fclean all

.PHONY: all debug clean fclean re bonus
