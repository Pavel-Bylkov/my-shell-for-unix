#ifndef MY_SHELL_H
# define MY_SHELL_H

# include <stdio.h>
# include <term.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>
# include "libft.h"
# include "get_next_line.h"

# define RL_BUFSIZE 128
# define ERRORS_FILE "./errors/errors.txt"

typedef struct	    s_error
{
    int                 code;
    char                *text;
    struct s_error  	*next;
}				    t_error;


typedef struct	    s_history
{
    char                *line;
    struct s_history    *prev;
    struct s_history	*next;
}				    t_history;

typedef struct	    s_redir
{
    char                f_spec[2];
    char                *out;
    struct s_history	*next;
}				    t_redir;

typedef struct	    s_pars
{
    int                 error;
    char                builtin;
    char                *path;
    char                **argv;
    char                f_spec[2];
    t_redir             *redirect;
    struct s_pars       *next;
}				    t_pars;

typedef struct      s_data
{
    int			        fd_hist;
    t_history           *history;
    t_pars              *curr_pars;
    char                **envp;
    t_error             *errors;
}                   t_data;

// t_pars				*ft_parsnew(char **argv, char f_spec);
// void				ft_parsadd_back(t_pars **lst, t_pars *new);
// void				ft_parsclear(t_pars **lst, void (*del)(void*));

// t_history			*ft_historynew(char *line);
// void				ft_lstadd_front(t_history **lst, t_history *new);
// void				ft_historyclear(t_history **lst, void (*del)(void*));
void	ft_new_list(t_history **list, char *str, int len);
void	ft_add_list(t_history **list, char *str, int len);
t_history	*ft_hist_create(t_history *hist, int fd_hist);
void	ft_change_struct(t_history **list, char *str);
void	ft_last_in_struct(t_history **list, char *str);

void                init_struct(t_data *data, char **envp);
void                load_history(t_data *data);
void save_history(t_data *data);
int                 main_loop(t_data *data);
void		        free_strs(char **s);
char                **copy_str_array(char **s);
int read_line(t_data *data);
int parse_line(t_data *data);
int run_comands(t_data *data);
int free_tmp_data(t_data *data);
void free_struct(t_data *data);
int                 ft_putchar(int c);
t_error 	*errors_create(void);
void		ft_exit_errcode(int errcode, t_data *data);
void		print_err(int errcode, t_data *data);

#endif
