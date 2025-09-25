NAME = minishell
CC = cc
LD = -lncurses -lreadline
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC_CORE =		builtins/ft_export_helper.c builtins/ft_hpwd.c builtins/ft_pwd.c \
				builtins/ft_builtin.c builtins/ft_cd.c builtins/ft_echo.c \
				builtins/ft_env.c builtins/ft_exit_builtin.c builtins/ft_export.c \
				builtins/ft_unset.c

SRC_ENV =		environ/ft_check_env.c environ/ft_env_gc.c environ/ft_env_lst.c \
				environ/ft_strjoin_env.c environ/ft_update_env.c \
				environ/ft_envstr_to_lst.c environ/ft_strdup_env.c \
				environ/ft_xtract_env.c environ/set_env.c

SRC_EXEC =		execution/exit_status.c execution/ft_exec.c execution/ft_exec_bin.c \
				execution/ft_read_stat.c execution/ft_redirection.c \
				execution/ft_heredocs.c execution/ft_lstenv_arr.c \
				execution/ft_termios.c

SRC_UTILS =		tools/check_operator.c tools/close_all_fd.c tools/ft_chdir.c \
				tools/ft_sighandler.c tools/ft_wait.c libft/ft_dup.c \
				tools/ft_getenv.c tools/ft_malloc.c tools/ft_open.c \
				tools/ft_counter.c tools/ft_execve.c tools/ft_exit.c \
				tools/ft_readline.c tools/ft_search_in_path.c

SRC_PARSE =		parsing/add_to_list.c parsing/check_valid.c parsing/count_token_len.c \
				parsing/ft_expand.c parsing/ft_token_lst.c parsing/ft_token_type.c \
				parsing/lexer.c parsing/lexer_helper.c parsing/parsering.c


SRC_LIB =		libft/ft_isspace.c libft/ft_itoa.c libft/ft_memcpy.c \
				libft/ft_atoi.c libft/ft_check_ambg.c libft/ft_isalnum.c \
				libft/ft_strlen.c libft/ft_strncmp.c libft/ft_strspn.c \
				libft/ft_putstr_fd.c libft/ft_split.c libft/ft_strchr.c \
				libft/ft_memset.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c \
				libft/ft_isalpha.c libft/ft_isallspace.c libft/ft_isdigit.c \
				libft/ft_strcmp.c libft/ft_strdup.c libft/ft_strjoin.c \
				libft/ft_xtract.c

MAIN_FIL =		main.c

SRCS	=	$(SRC_CORE) $(SRC_ENV) $(SRC_EXEC) \
		$(SRC_UTILS) $(SRC_LIB) $(SRC_PARSE) $(MAIN_FIL)

OBJS = 	$(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS)  $(OBJS)  $(LD) -o $@

%.o : %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: clean fclean re
