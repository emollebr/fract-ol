# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emollebr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/03 17:44:23 by emollebr          #+#    #+#              #
#    Updated: 2023/04/28 15:06:40 by emollebr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fractol
CFLAGS = -Werror -Wall -Wextra
MINILIBXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
SRCS=src/init.c
OBJS=src/init.o

${NAME}: ${OBJS}
	cc -o ${NAME} $^ $(MINILIBXFLAGS)

.c.o: ${SRCS}
	cc ${CFLAGS} -c -o $@ $< ${INCLUDES_DIR} -Imlx_linux -O3

clean:
	rm ${OBJS}

all:	${NAME}

re:	clean all	
