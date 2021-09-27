# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/24 19:45:52 by nagrivan          #+#    #+#              #
#    Updated: 2021/09/24 19:46:28 by nagrivan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRCS	=	
			
OBJS	= ${SRCS:.c=.o}

INCLUDES	= minishell.h

CC	= gcc

CFLAGS	= -g -Wall -Wextra -Werror

RM	= rm -rf

all: $(NAME)

%.o : %.c ${INCLUDES}
		${CC} ${CFLAGS} -c $< -o $@

$(NAME): ${OBJS}
		 ${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

norma:
		norminette ${SRCS} ${INCLUDES}

.PHONY: all clean fclean re norma