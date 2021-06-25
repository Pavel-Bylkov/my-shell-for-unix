#ifndef MY_SHELL_H
# define MY_SHELL_H

# include <stdio.h>
//# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>
# include "libft.h"
# include "get_next_line.h"

# define ERRORS_FILE "./errors/errors.txt"
# define HISTORY_FILE "./.history"
# define SHELL_PROMT "my_shell>$ "
# define ERROR_PREFIX "my_shell: "
# define QUAOTE_PROMT "> "
# ifndef DEBUG
#  define DEBUG	0
# endif

typedef struct	    s_error
{
    int                 code;
    char                *text;
    struct s_error  	*next;
}				    t_error;


typedef struct		s_tmp_files
{
	int					index;
	char				*fname;
	struct s_tmp_files	*next;
}					t_tmp_files;

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

typedef struct             s_fdesk
{
    int                 **fd;
    int                 fd_r;
    int                 fd_w;
}                       t_fdesk;

typedef struct	    s_pars
{
    int                 count;
    int                 error;
    char                *path;
    char                **argv;
    char                f_spec[10];
    t_redir             *redirect;
    struct s_pars       *next;
}				    t_pars;

typedef struct      s_data
{
	char				*line;
	t_tmp_files			*tmp_files;
	int					count_files;
	t_pars				*curr_pars;
	t_pwdpath			*pwd_oldp;
	t_fdesk             *fdesk;
	char                **envp;
	int                 *index;  //* массив индексов (строк) массива envp
	int                 size;   //* размер массива
	t_error             *errors;
	int					code_exit;
	int					count_malloc;
}                   t_data;

#ifdef  MAIN_FILE
t_data						*g_data;
#else
extern t_data				*g_data;
#endif

t_pars		        *ft_parsnew(int error, char *path, char **argv, char *f_spec);
void		        ft_parsadd_back(t_pars **lst, t_pars *new);
void		        ft_parsadd_front(t_pars **lst, t_pars *new);
void				ft_parsclear(t_pars **lst);


//void rl_replace_line(char *s, int k);
void	            ft_strcopy_fr(char **line, char *str);
void                init_struct(t_data *data, char **envp);
int                 one_run(t_data *data, char *str);
void                main_loop(t_data *data);
void		        int_handler2(int status);
int			        is_endl_ignor(char *str, t_data *data);
int                 read_from_file(t_data *data, char *filename);
int		            check_unexpected_token(char *str);
void		        free_array(void **s);
int                 parse_line(t_data *data, int error);
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
void				g_free(void *content);
void				*g_malloc(size_t size);
char				*g_strdup(char *str);
char				*g_strdupn(const char *str, size_t len);
char				*g_strjoin(char *str1, int n, int k, char *str2);
char				*g_newpath(char *dir, int n, char *name);
int					ft_perr(char *com, int code, char *str1, char *str2);
int			        brackets_is_open(char *str, int n);
int			        ft_stdin_active(char *str, t_data *data);
char	            *quaote_backslash_clean(char *str);
void				g_tmp_files_clear(t_tmp_files **lst);
int		        	read_tmp_stdin(t_data *data, char *str);
t_tmp_files			*tmp_files_new(int index, char *fname);
int					tmp_files_size(t_tmp_files *lst);
void				tmp_files_add_back(t_tmp_files **lst, t_tmp_files *new);
char				*get_filename_by_index(t_tmp_files *head, int index);
int					unexpected_eof(char *str);
int					unexpected_eof_infile(char *str);

int		            ft_export(t_data *data, t_pars *pars);
void	            ft_out_export(t_data data);
void	            init_data(char **env, t_data *data);
void	ft_init_fd_aam(t_data *data, t_fdesk **fd);
int		            aam_main(t_data *data);
char	            *ft_strcpy_fr(char *str1, char *str2);
int		            ft_strcmp(const char *s1, const char *s2);
void	            create_index(t_data *data);
void	ft_shlvl_incr_add_aam(char **str);
void	            sort_mass(char **mas, int *id[], int size);
void	ft_open_file(int *fd, t_redir *red, int k, int key);
void	ft_free_fd_aam(t_fdesk **fd);
void	ft_swap(int *a, int *b);
int		            ft_char_in_str(char *str, char c);
char	            **ft_env_add(t_data *data, char *str, int *size);
int	            ft_export_output_err(int code, char *str);
void	ft_unset_output_err(char *str);
int		            ft_unset(t_data *data, t_pars pars);
char	**ft_env_del(t_data *data, char *str, int *size);
char	**ft_free_mas(char **mas);
int	ft_env(t_data *data, t_pars pars);
void	ft_env_output(t_data *data);
void	ft_env_output_err(char *str);
int	ft_exit(t_pars par);
void	ft_exit_output_err(char *str1, char *str2);
int	ft_pwd(void );
int	ft_cd(t_data *data, t_pars *pars);
int	ft_cd_path(t_data *data, char **path);
int ft_path_back(t_data *data, char **path);
char	*ft_path_home(t_data *data);
char	*ft_strjoin_path(char *str1, char *str2);
int	ft_pos_env_aam(t_data *data, char *str);
void	ft_replace_oldpwd(t_data *data, char *path);
int	ft_pos_env_aam(t_data *data, char *str);
void	ft_replace_oldpwd(t_data *data, char *path);
int	ft_echo(t_pars pars);
int	ft_del_position(t_data data, char *str);
void	init_pwd_aam(t_data *data);
int		ft_redirect_aam(t_pars *pars, t_fdesk *fd);
void	ft_pipe_open_aam(t_pars *pars, t_fdesk *fd);
void	ft_pipe_close_aam(t_pars *pars, t_fdesk *fd);
void	ft_binar_subsidiary_aam(t_data *data, t_pars *pars);
int	ft_binar_command_aam(t_data *data, t_pars *pars);
int	ft_command_err_aam(char *name_f);
int	ft_output_err_aam(int code, char *str1, char *str2, char *str3);
int	ft_chrstr_in_set(char *str, char *set, int n);
int	ft_choice_command_aam(t_data *data);
int	ft_choice_command_waitpid(int j);
int	ft_choice_command_build(t_pars *pars, t_data *data);
void	ft_choice_command_pipe(t_data *data, t_pars *pars);
int	ft_build_in_aam(t_data *data, t_pars *pars);
void	ft_build_open_aam(t_fdesk *fd, int *fd_st0, int *fd_st1);
void	ft_build_close_aam(t_fdesk *fd, int *fd_st0, int *fd_st1);


#endif
