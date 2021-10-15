# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/24 19:45:52 by nagrivan          #+#    #+#              #
#    Updated: 2021/10/15 14:38:02 by nagrivan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

LIBFT	= ./libft/libft.a

LIBFT_INCLUDES	= ./libft/libft.h

SRCS_DIRS	=	bildins/	local_func/

VPATH	=	${SRCS_DIRS}
			
SRCS		=	main.c \
				my_cd.c		my_echo.c	my_env.c	my_exit.c	my_export.c		my_pwd.c	my_unset.c \
				my_pipe.c	my_redirections.c	start_minishell.c \

OBJS_DIRS	=	.objs/

OBJS	= ${addprefix ${OBJS_DIRS}, ${notdir ${SRCS:.c=.o}}}

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