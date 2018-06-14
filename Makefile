# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/14 15:41:10 by tkiselev          #+#    #+#              #
#    Updated: 2018/06/14 16:31:07 by tkiselev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM_IN=lem-in
LIB=libft.a
CC_FLAGS=-Wall -Wextra -Werror
SRCS=algorithm.c generate_ways.c is_functions.c links.c main.c output.c \
	 parsing.c rooms.c staff.c
OBJ=$(patsubst %, %.o, $(basename $(SRCS)))
HEADER=lem_in.h
LIB_DIR=libft

all: $(LEM_IN)

$(LEM_IN): $(OBJ) $(LIB)
	gcc $(CC_FLAGS) -o $(LEM_IN) $(OBJ) $(LIB_DIR)/$(LIB)

$(LIB):
	make -c $(LIB_DIR)
