#ifndef MY_SHELL_H
# define MY_SHELL_H

# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
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
    char                f_spec[10];
    char                *out;
    struct s_redir  	*next;
}				    t_redir;

typedef struct	    s_pars
{
    int                 error;
    char                *path;
    char                **argv;
    char                f_spec[10];
    t_redir             *redirect;
    struct s_pars       *next;
}				    t_pars;

typedef struct      s_data
{
    int			        fd_hist;
    t_history           *history;
    char                insert_flag;
    t_pars              *curr_pars;
    char                **envp;
    int                 *index;  //* массив индексов (строк) массива envp
    int                 size;   //* размер массива
    t_error             *errors;
}                   t_data;

t_pars		        *ft_parsnew(int error, char *path, char **argv, char *f_spec);
void		        ft_parsadd_back(t_pars **lst, t_pars *new);
void				ft_parsclear(t_pars **lst);

t_history		    *new_history(char *str);
void	            history_add_front(t_history **lst, t_history *new);
void				ft_historyclear(t_history **lst);
t_history	        *ft_hist_create(t_history *hist, int fd_hist);
void	            ft_change_struct(t_history **list, char *s);
void	            ft_last_in_struct(t_history **list, char *str);
void	            ft_key_backspace(t_history **hist, char **line, int *pos);
void	            ft_key_right(char *line, int *pos);
void	            ft_key_left(int *pos);
void	            ft_key_down(t_history **hist, char **line, int *pos);
void	            ft_key_up(t_history **hist, char **line, int *pos);
void	            ft_strcopy_fr(char **line, char *str);
void                ft_press_key(t_data *data, char **line, int pos);
char	            *ft_del_symbol(char *str, int i);
void                init_struct(t_data *data, char **envp);
void                load_history(t_data *data);
void                save_history(t_data *data);
int                 main_loop(t_data *data);
void		        free_array(void **s);
//char                **copy_str_array(char **s);
int                 read_line(t_data *data);
int                 parse_line(t_data *data, int error);
char			    **argv_split(char *s);
int                 run_comands(t_data *data, int error);
void                free_struct(t_data *data);
int                 ft_putchar(int c);
t_error             *errors_create(void);
void				ft_errorsclear(t_error **lst);
void		        ft_exit_errcode(int errcode, t_data *data);
int		            print_err(int errcode, t_data *data);
int			        quaote_is_open(char *str, int n);
int                 backslash_is_active(char *str, int n);
t_pars		        *ft_parsnew(int error, char *path, char **argv, char *f_spec);
void		        ft_parsadd_back(t_pars **lst, t_pars *new);
void				ft_parsclear(t_pars **lst);
char	            **get_commands(t_data *data);

int		            ft_export(t_data *data, t_pars pars);
void	            ft_out_export(t_data data);
void	            init_data(char **env, t_data *data);
int		            aam_main(t_data *data);
char	            *ft_strcpy_fr(char *str1, char *str2);
int		            ft_strcmp(const char *s1, const char *s2);
void	            create_index(t_data *data);
void	            sort_mass(char **mas, int *id[], int size);
int		            ft_char_in_str(char *str, char c);
char	            **ft_env_add(t_data *data, char *str);
void	            ft_export_output_err(char *str);

#endif
