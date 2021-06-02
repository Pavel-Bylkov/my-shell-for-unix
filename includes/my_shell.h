#ifndef MY_SHELL_H
# define MY_SHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>

# define RL_BUFSIZE 128

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
    char                *path;
    char                **argv;
    char                f_spec[2];
    t_redir             *redirect;
    struct s_pars       *next;
}				    t_pars;

typedef struct      s_data
{
    t_history           *history;
    t_pars              *curr_pars;
    char                **envp;
}                   t_data;

t_pars				*ft_parsnew(char **argv, char f_spec);
void				ft_parsadd_back(t_pars **lst, t_pars *new);
void				ft_parsclear(t_pars **lst, void (*del)(void*));

t_history			*ft_historynew(char *line);
void				ft_lstadd_front(t_history **lst, t_history *new);
void				ft_historyclear(t_history **lst, void (*del)(void*));

void                init_struct(t_data *data, char **envp);
void                load_history(t_data *data);
int                 main_loop(t_data *data);
void		        free_strs(char **s);
char                **copy_str_array(char **s);


#endif
