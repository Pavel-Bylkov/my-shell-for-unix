#ifndef MY_SHELL_H
# define MY_SHELL_H

# include <stdio.h>
# include <curses.h>
# include <readline/readline.h> // для маков возможно нужно убрать папку
# include <readline/history.h>
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
# define HISTORY_FILE "./.history"
# define SHELL_PROMT "my_shell>$ "

typedef struct	    s_error
{
    int                 code;
    char                *text;
    struct s_error  	*next;
}				    t_error;


typedef struct	    s_redir
{
    char                f_spec[10];
    char                *out;
    struct s_redir  	*next;
}				    t_redir;

typedef struct          s_pwdpath
{
    char                *pwd_p;
    char                *oldpwd_p;
}                       t_pwdpath;


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
    char				*line;
    char                insert_flag;
    t_pars              *curr_pars;
    t_pwdpath           *pwd_oldp;
    char                **envp;
    int                 *index;  //* массив индексов (строк) массива envp
    int                 size;   //* размер массива
    t_error             *errors;
}                   t_data;

t_pars		        *ft_parsnew(int error, char *path, char **argv, char *f_spec);
void		        ft_parsadd_back(t_pars **lst, t_pars *new);
void				ft_parsclear(t_pars **lst);


void	            ft_strcopy_fr(char **line, char *str);
void                init_struct(t_data *data, char **envp);
int                 main_loop(t_data *data);
void		        free_array(void **s);
int                 read_line(t_data *data);
int                 parse_line(t_data *data);
char			    **argv_split(char *s);
int                 run_comands(t_data *data, int error);
void	            print_pars(t_data *data);
void                free_struct(t_data *data);
int                 ft_putchar(int c);
t_error             *errors_create(void);
void				ft_errorsclear(t_error **lst);
void		        ft_exit_errcode(int errcode, t_data *data);
int		            print_err(int errcode, t_data *data);
int	                chr_in_str(char c, char *s);
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
void	ft_unset_output_err(char *str);
int		            ft_unset(t_data *data, t_pars pars);
char	**ft_env_del(t_data *data, char *str);
char	**ft_free_mas(char **mas);
int	ft_env(t_data *data, t_pars pars);
void	ft_env_output(t_data *data);
void	ft_env_output_err(char *str);
int	ft_exit(t_pars par);
int	ft_pwd(void);
int	ft_cd(t_data *data, t_pars *pars);
char *ft_path_back(t_data *data);
char	*ft_path_home(t_data *data);
void	ft_cd_output_err(char *str1, char *str2);
int	ft_pos_env_aam(t_data *data, char *str);
void	ft_replace_oldpwd(t_data *data, char *path);
int	ft_pos_env_aam(t_data *data, char *str);
void	ft_replace_oldpwd(t_data *data, char *path);
int	ft_echo(t_pars pars);


#endif
