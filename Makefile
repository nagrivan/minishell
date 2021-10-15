# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/24 19:45:52 by nagrivan          #+#    #+#              #
#    Updated: 2021/10/15 16:21:20 by nagrivan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

LIBFT_DIRS	= ./libft/

LIBFT	= ${LIBFT_DIRS}libft.a

LIBFT_INCLUDES	= ${LIBFT_DIRS}libft.h

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

$(OBJS_DIRS):
		@mkdir -p $@

$(OBJS_DIRS)%.o : %.c ${INCLUDES} ${LIBFT_INCLUDES} ${LIBFT}
		${CC} ${CFLAGS} -c $< -o $@

$(NAME): ${OBJS} ${OBJS_DIRS} ${LIBFT} Makefile
		 ${CC} ${CFLAGS} ${OBJS} ${OBJS_BILD} ${LIBFT} -o ${NAME} -lreadline ${LDFLAGS} ${CPPFLAGS}

$(LIBFT):
		make -C ${LIBFT_DIRS}
clean:
		make clean -C ${LIBFT_DIRS}
		${RM} ${OBJS_DIRS}

fclean: clean
		make -C ${LIBFT_DIRS}
		${RM} ${NAME}

re: fclean all

norma:
		norminette ${SRCS} ${INCLUDES}

.PHONY: all clean fclean re norma