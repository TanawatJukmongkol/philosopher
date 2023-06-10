# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 05:42:52 by tjukmong          #+#    #+#              #
#    Updated: 2023/06/10 16:42:20 by tjukmong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
SRCS		= philo.c table.c utils.c philosopher.c

SRC_DIR		= ./
LIB_DIR		= ./lib/
BUILD_DIR	= ./build/

SRC			= ${addprefix ${BUILD_DIR},${SRCS}}
OBJ			= ${SRC:.c=.o}

CC			= cc
CFLAG		= -g -Wall -Werror -Wextra -O3 -fsanitize=address
# CFLAG		= -g -Wall -Werror -Wextra -O3
# CFLAG		= -g -fsanitize=address

all: library ${BUILD_DIR} ${NAME}

library:
	find ${LIB_DIR} -mindepth 1 -maxdepth 1 -exec make -C {} \;

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f ${NAME}
	find ${LIB_DIR} -mindepth 1 -maxdepth 1 -exec make -C {} fclean \;

re: fclean all

${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

${BUILD_DIR}%.o:${SRC_DIR}%.c
	$(CC) $(CFLAG) -c -o $@ $^

${NAME}: ${OBJ}
	$(CC) ${OBJ} ${wildcard ${LIB_DIR}/*/*.a} -o ${NAME} $(CFLAG)

.PHONY:	all library clean fclean re
