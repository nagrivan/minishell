# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/24 19:45:52 by nagrivan          #+#    #+#              #
#    Updated: 2021/11/14 16:00:01 by nagrivan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

LIBFT_DIRS	= ./libft/

LIBFT	= ${LIBFT_DIRS}libft.a

LIBFT_INCLUDES	= ${LIBFT_DIRS}libft.h

SRCS_DIRS	=	bildins/	local_func/

VPATH	=	${SRCS_DIRS}
			
SRCS		=	main.c \
				my_cd.c			cd_utils.c			my_echo.c			my_env.c \
				my_export.c		exp_uns_utils.c		my_pwd.c			my_unset.c \
				my_exit.c 		sort.c\
				my_pipe.c		my_redirections.c	start_minishell.c	my_signal.c\

OBJS_DIRS	=	.objs/

OBJS	= ${addprefix ${OBJS_DIRS}, ${notdir ${SRCS:.c=.o}}}

INCLUDES	= minishell.h

CC	= gcc

CFLAGS	= -g -Wall -Wextra -Werror

LDFLAGS		= -L/Users/nagrivan/.brew/opt/readline/lib

CPPFLAGS	= -I/Users/nagrivan/.brew/opt/readline/include

RM	= rm -rf

all: libft_make $(NAME)

$(OBJS_DIRS):
		@mkdir -p $@

$(OBJS_DIRS)%.o : %.c ${INCLUDES} ${LIBFT_INCLUDES} ${LIBFT}
		${CC} ${CFLAGS} -c $< -o $@

$(NAME): ${OBJS_DIRS} ${OBJS} ${LIBFT} Makefile
		 ${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME} -lreadline ${LDFLAGS} ${CPPFLAGS}

libft_make:
		make -C ${LIBFT_DIRS}
clean:
		make clean -C ${LIBFT_DIRS}
		${RM} ${OBJS_DIRS}

fclean: clean
		make fclean -C ${LIBFT_DIRS}
		${RM} ${NAME}

re: fclean all

.PHONY: clean fclean re norma