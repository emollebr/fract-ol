# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emollebr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/03 17:44:23 by emollebr          #+#    #+#              #
#    Updated: 2023/05/23 14:10:21 by emollebr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fractol
CFLAGS := -Werror -Wall -Wextra
MLXFLAGS := -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
LIBFTFLAGS := -Imy_lib -Lmy_lib
LIBFT := ./my_lib/
MLX := ./mlx_linux/
LIBS := $(MLX)/libmlx_Linux.a $(LIBFT)/my_lib.a
SRCS :=src/init.c src/utils.c src/fractals.c src/controls.c
OBJS := ${SRCS:.c=.o}

${NAME}:  $(OBJS) $(LIBS) 
	 cc $^ ${MLXFLAGS} ${LIBFTFLAGS} -o ${NAME} 

all:	libft mlx ${NAME}

libft: 
	make -C ${LIBFT}

mlx: 	
	wget https://cdn.intra.42.fr/document/document/12154/minilibx-linux.tgz
	tar -xvzf minilibx-linux.tgz
	mv minilibx-linux mlx_linux
	rm -rf minilibx-linux.tgz
	make -C ${MLX} 

.c.o:   ${SRCS}
	cc ${CFLAGS} -I. -Imy_lib -Imlx_linux -c -o $@ $<  -O3	 

clean:
	rm -f ${OBJS} && cd ./my_lib && make clean && cd ..

fclean:
	rm -f ${NAME} ./my_lib/my_lib.a && rm -rf ./mlx_linux

re:	clean all
