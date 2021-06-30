NAME		= minishell

LIBDIR		= ./libft/
LIBFT		= $(LIBDIR)libft.a

LIBFLAGS	= -L libft -lft -lreadline -ltermcap -L/usr/local/opt/readline/lib  #-L/Users/aamarei/.brew/opt/readline/lib 

CFLAGS		= -Wall -Wextra -Werror
CC			= gcc -g

INCLUDES	= -I ./includes/. -I $(LIBDIR)includes/. -I/usr/local/opt/readline/include #-I/Users/aamarei/.brew/opt/readline/include
HEADER		= ./includes/minishell.h

SRCDIR		= ./sources/
OBJDIR		= ./objs/

FLS			= \
			main \
			init_structs \
			mainloop \
			check_line \
			pars_and_run \
			parser \
			pars_struct \
			pars_command \
			brakets_clean \
			insert_env_var \
			get_var_name \
			replace_path \
			read_stdin \
			split_argv \
			split_command \
			split_tools \
			redirects \
			get_redirects \
			quaote_open \
			rl_with_hist \
			rl_without_hist \
			term_rl \
			term_read \
			term_keys \
			tmp_files_tools \
			str_utils \
			tools \
			errors \
			clears \
			ft_minishell_pipe_aam \
			ft_str_utils_aam \
			ft_export_main_aam \
			ft_export_aam \
			ft_unset_main_aam \
			ft_unset_aam \
			ft_env_main_aam \
			ft_exit_main_aam \
			ft_pwd_main_aam \
			ft_cd_main_aam \
			ft_cd_aam \
			ft_echo_main_aam \
			ft_output_err_aam \
			ft_cd_path_aam \
			ft_minishell_main_aam \
			ft_minishell_init_aam \
			ft_minishell_choice_aam \
			ft_minishell_utils_aam \
			ft_minishell_build_aam

SRC			= $(FLS)

OBJ			= $(addprefix $(OBJDIR), $(SRC:=.o))
DFLS		= $(SRC:=.d)

all: $(LIBFT)
	$(MAKE) $(NAME)

$(OBJ):			$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)
	@$(CC)		$(CFLAGS) $(INCLUDES) -c $< -o $@ -MMD
	@echo "Compiled $@"

$(NAME):		$(OBJDIR) $(LIBFT) $(OBJ)
	@echo '----Making minishell ------'
	#@make		-C libft/
	$(CC)		$(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFLAGS) -o $(NAME)
	@echo "Ready"

$(OBJDIR):
	@mkdir -p $@

include $(wildcard $(addprefix $(OBJDIR), $(DFLS)))

$(LIBFT):	FORCE
	@echo '---Making libft ------'
	$(MAKE) -C $(LIBDIR)
	@echo 'Making libft done'

FORCE:

clean:
	$(MAKE) clean	-C $(LIBDIR)
	rm -rf		$(OBJDIR) *.o *.d

fclean:		clean
	$(MAKE) fclean	-C $(LIBDIR)
	rm -f		$(NAME)
	rm -rf		.*.tmp *.tmp

re:		fclean
	$(MAKE)

norma:
	norminette $(SRCDIR) $(LIBDIR)srcs/*.c $(LIBDIR)includes/*.h ./includes/

bonus:	all

.PHONY: all debug clean fclean re bonus
