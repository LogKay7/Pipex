# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkailany <lkailany@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/23 15:16:54 by lkailany          #+#    #+#              #
#    Updated: 2022/04/18 12:19:37 by lkailany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = pipex

CFLAGS = -Wall -Wextra -Werror

SRCS = src/main.c src/ft_printf.c src/utils.c src/parsing.c src/ft_split.c 

OBJS = ${SRCS:.c=.o}

${NAME}: ${OBJS}
	${CC} ${OBJS} -o ${NAME}

all: ${NAME}

clean: 
		rm -rf ${OBJS}

fclean: clean
		rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re