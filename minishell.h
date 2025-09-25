/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchah <mbenchah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:56:16 by aanbadi           #+#    #+#             */
/*   Updated: 2025/06/16 19:00:24 by mbenchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>

# define OPEN_MAX 1024
# define PATH_MAX 4096

# define SNTX_ERR "minishell: syntax error near unexpected token\n"
# define MSERR "minishell: : command not found\n"

# define T_CMND				0
# define T_ARG				1
# define T_DOLLAR_EXPAND	2
# define T_IGN				3
# define T_DOUBLE_GREATER	4
# define T_DOUBLE_LESS		5
# define T_DOUBLE_QUOTE		6
# define T_EXIT_STATUS		7
# define T_EXPANDED			8
# define T_GREATER			9
# define T_LESS				10
# define T_PIPE				11
# define T_SINGLE_DOLLAR	12
# define T_SINGLE_QUOTE 	13

# define AF_S				0
# define NEW				1
# define CMD				0
# define RET				1
/*---------------------- STRUCTS --------------------*/

typedef struct s_token
{
	char			*value;
	int				type;
	int				a_sp;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*equal;
	char			*value;
	struct s_env	*next;

}					t_env;

typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;

}					t_gc;

typedef struct s_redirect
{
	t_token			file;
	int				type;
}					t_redirect;

typedef struct s_cmd
{
	t_token			**tokens;
	t_redirect		**files;
	int				hdoc_indx;
	int				last;
}					t_cmd;

typedef struct s_builtin
{
	char			*name;
	int				(*func)(t_cmd);
}					t_builtin;

/*--------------------FUNCTIONS-------------------*/

void				exit_builtin(t_cmd cmd, int print_exit);
int					cd_builtin(t_cmd cmd);
int					env_builtin(t_cmd cmd);
int					echo_builtin(t_cmd cmd);
t_env				*ft_sort_env(t_env *env);
void				*ft_lstlast(t_env *lst);
t_env				*ft_lstenv_dup(void);
int					export_print(void);
int					exec_builtin(t_cmd cmd);
void				export_handle_argument(t_env *node);
int					handle_export_argument(char *arg);
int					pwd_builtin(t_cmd cmd);
int					export_builtin(t_cmd cmd);
int					is_builtin(t_cmd cmd);
int					unset_builtin(t_cmd cmd);

int					ft_envchr(char *key);
int					check_valid_env_key(char *key);

void				free_env(void);
t_gc				**ft_env_gc(void);

t_env				**ft_env_head(void);
void				set_env(char **input);
void				ft_update_env(char *key, char *value);
void				ft_append_env(char *key, char *value);

char				*get_cmd_path(char *executable);
char				**ft_arg_arr(t_cmd cmd);
char				**ft_lstenv_arr(char *cmd);

int					ft_exec(t_cmd *cmds, int n_cmds, int n_hdocs);
int					exec_bin(t_cmd cmd, int fd_in, char **hdoc, int *last_pid);
int					process_cmd_heredocs(t_cmd *cmd, char **heredoc,
						int hdoc_count);
int					ft_heredoc(t_cmd *cmds, int n_cmds, char **heredoc);
void				unlink_heredoc(char **heredoc, int num_heredocs);
char				*read_from_heredoc(t_redirect *redirect, char *name);
int					ft_redirection(t_cmd *cmd, char **heredoc,
						int hdoc_indx);
void				sigint_handler(int signal);
int					count_args(t_cmd cmd, int *j);
void				ft_lstadd_back_env(t_env *new);
t_env				*ft_envstr_to_lst(char *str);

t_env				*ft_lstnew_env(char *key, char *equal, char *value);
int					ft_lstsize(t_env *env);
char				*ft_strjoin_env(char const *s1, char const *s2);
char				*ft_strdup_env(const char *s1);
char				*ft_xtract_env(const char *start, const char *end);

int					count_cmds(t_token *token);
int					count_tokens(t_token *token);
int					count_files(t_token *token);
int					count_hdoc(t_token *token);

int					check_redirect(int type);
int					check_operator(t_token *token);
int					ft_token_type(const char *value);
int					all_dollar(char *str);

void				ft_exit(int status);
void				ft_execve(t_cmd cmd);
char				*ft_getenv(char *str);
int					ft_chdir(char *path);
char				*ft_readline(const char *prompt);
int					ft_open(char *path, int oflag, int mode);

int					ft_strchr(const char c, const char *charset);
int					ft_isalnum(int c);
int					ft_isallspace(char *str);
int					ft_isdigit(int c);
int					ft_isspace(char c);
int					ft_isalpha(int c);
char				*check_home(char *value, int token_type);

void				ft_free(void);
void				*ft_malloc(size_t size);
void				*ft_malloc_env(size_t size);

struct termios		*ft_get_termios(void);
char				*ft_hpwd(char *str, int flg);
int					count_word(char const *s, char c);
void				int_smp_handler(int signal);
void				*ft_memset(void *b, int c, size_t len);

void				set_signals(void);
void				*ft_memcpy(void *dst, const void *src, size_t n);
int					add_list(t_token **token, char *value, int typ, int *spc_n);
char				*search_in_path(char *bin, char **path_dirs);

char				*ft_itoa(int n);
int					ft_atoi(const char *nbr);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putchar_fd(char c, int fd);
int					check_all_quotes(char *input);

void				ft_putendl_fd(char *s, int fd);
char				**ft_split(char const *s, char c);
char				*ft_xtract(const char *start, const char *end);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);

int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlen(const char *s);
int					expand_token(t_token **token, char *s, int a_s, int *cmd);
size_t				ft_strspn(const char *str, const char *accept);
void				ft_wait(pid_t pid);
int					check_valid_xpnd(int c);
int					check_ambg(char *str, char *accept);
char				*expand_in_qoute(char *input);
void				ft_lstadd_back_token(t_token **lst, t_token *new);
t_token				*ft_lstnew_token(char *value, int type,
						int a_sp);
t_token				*ft_last_token(t_token **lst);
void				count_token_len(char **input, size_t i);

t_token				*lexer(void);
t_cmd				*parsering(t_token *token);
int					check_valid_qoutes(const char *input);
int					check_valid_op(t_token *token);
int					ft_dup(int fd);
int					ft_dup2(int oldfd, int newfd);

int					*ft_get_read_stat(void);
void				ft_set_read_stat(int stat);
void				close_all_fds(void);
int					*ft_get_status(void);
void				ft_set_status(int status);
int					ft_s_ret(int in);

#endif
