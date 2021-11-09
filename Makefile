# Это тестовый Makefile для сборки и запуска тестов до написания основного парсера

# my_cd.c	my_echo.c	my_env.c	my_exit.c	my_export.c		my_pwd.c	my_unset.c

NAME	= minitest

LIBFT	= ./libft/libft.a

SRCS	=	main_test.c		start_minishell.c		my_redirections.c		my_pipe.c		my_signal.c\

SRCS_BILD	=	my_pwd.c \
				my_echo.c \
				my_exit.c \
				my_env.c \
				my_cd.c \
				my_export.c \
				my_unset.c \

OBJS	= ${SRCS:.c=.o}

OBJS_BILD	= ${SRCS_BILD:.c=.o}

LIBFT_INCLUDES	= ./libft/libft.h

INCLUDES	= minishell.h

CC	= gcc

CFLAGS	= -g -Wall -Wextra -Werror

LDFLAGS		= -L/Users/nagrivan/.brew/opt/readline/lib

CPPFLAGS	= -I/Users/nagrivan/.brew/opt/readline/include

RM	= rm -rf

all: $(NAME)

%.o : %.c ${INCLUDES} ${LIBFT_INCLUDES}
		${CC} ${CFLAGS} -c $< -o $@

$(NAME): ${OBJS} ${OBJS_BILD} ${LIBFT}
		 ${CC} ${CFLAGS} ${OBJS} ${OBJS_BILD} ${LIBFT} -o ${NAME} -lreadline ${LDFLAGS} ${CPPFLAGS}

$(LIBFT):
		make -C libft/
clean:
		${RM} ${OBJS} ${OBJS_BILD}

fclean: clean
		${RM} ${NAME}

re: fclean all

norma:
		norminette ${SRCS} ${INCLUDES}

.PHONY: all clean fclean re norma