# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/24 19:45:52 by nagrivan          #+#    #+#              #
#    Updated: 2021/12/03 13:25:21 by ralverta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

LIBFT_DIRS	= ./libft/

LIBFT	= ${LIBFT_DIRS}libft.a

LIBFT_INCLUDES	= ${LIBFT_DIRS}libft.h

SRCS_DIRS	=	bildins/	local_func/		parser/

VPATH	=	${SRCS_DIRS}
			
SRCS		=	main.c \
				my_cd.c			cd_utils.c			my_echo.c			my_env.c \
				my_export.c		exp_uns_utils.c		my_pwd.c			my_unset.c \
				my_exit.c		cd_utils_2.c		sort.c				init.c\
				\
				my_heredoc.c	my_heredoc_sign.c	work_patch.c		one_command.c\
				my_pipe.c		my_redirections.c	start_minishell.c	my_signal.c\
				\
				dollar.c		parser.c			argv_redir.c		nodes.c\
				quotes.c		errors.c			dollar_adds.c		utils.c\

OBJS_DIRS	=	.objs/

OBJS	= ${addprefix ${OBJS_DIRS}, ${notdir ${SRCS:.c=.o}}}

INCLUDES	= minishell.h

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror #-g -fsanitize=address 
LDFLAGS		= -L${HOME}/.brew/opt/readline/lib/

CPPFLAGS	= -I${HOME}/.brew/opt/readline/include/ -I./

RM	= rm -rf

all: $(NAME)

$(OBJS_DIRS):
		@mkdir -p $@

$(OBJS_DIRS)%.o : %.c ${INCLUDES} ${LIBFT_INCLUDES} ${LIBFT}
		${CC} ${CFLAGS} -c $< -o $@ $(CPPFLAGS)

$(NAME): ${OBJS_DIRS} ${OBJS} ${LIBFT} Makefile
		 ${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME} -lreadline ${LDFLAGS} ${CPPFLAGS}

$(LIBFT):
		make -C ${LIBFT_DIRS}
clean:
		make clean -C ${LIBFT_DIRS}
		${RM} ${OBJS_DIRS}

fclean: clean
		make fclean -C ${LIBFT_DIRS}
		${RM} ${NAME}

re: fclean all

.PHONY: clean fclean re norma
