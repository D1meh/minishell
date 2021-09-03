NAME	= minishell

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

SRCS	=	minishell.c \
			commands/exit.c \
			commands/env.c \
			commands/pwd.c \
			commands/export.c \
			commands/utils.c \
			commands/unset.c \
			commands/echo.c \
			commands/cd.c \
			\
			sys/builtin.c \
			sys/create_token.c \
			sys/dollar.c \
			sys/error.c \
			sys/get_quote.c \
			sys/init_var.c \
			sys/interpreter.c \
			sys/left_prompt.c \
			sys/lexer_utils.c \
			sys/parser.c \
			sys/piper.c \
			sys/piper_utils.c \
			sys/redirections.c \
			sys/signal.c \
			sys/token_utils.c \
			\
			libft/ft_exist.c \
			libft/ft_freetab.c \
			libft/ft_gnl.c \
			libft/ft_is_smth.c \
			libft/ft_itoa.c \
			libft/ft_putendl.c \
			libft/ft_putstr_fd.c \
			libft/ft_putstr.c \
			libft/ft_realloc.c \
			libft/ft_split.c \
			libft/ft_strcat.c \
			libft/ft_strchr.c \
			libft/ft_strcmp.c \
			libft/ft_strdup.c \
			libft/ft_strjoin.c \
			libft/ft_strlen.c \
			libft/ft_substr.c \
			libft/ft_varadd_back.c \
			libft/ft_varadd_front.c \
			libft/ft_varclear.c \
			libft/ft_vardel.c \
			libft/ft_varexist.c \
			libft/ft_varlast.c \
			libft/ft_varnew.c \
			libft/ft_varreplace.c \
			libft/ft_varsize.c \

OBJS	= $(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) ./includes/libreadline.a -lreadline -lncurses -o $(NAME) $(OBJS)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
