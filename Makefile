# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/14 15:41:10 by tkiselev          #+#    #+#              #
#    Updated: 2018/06/15 19:40:35 by tkiselev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM_IN=lem-in
LIB=libftprintf.a
CC_FLAGS=-Wall -Wextra -Werror
SRCS=algorithm.c generate_ways.c is_functions.c links.c main.c output.c \
	 parsing.c rooms.c staff.c
OBJ=$(SRCS:.c=.o)
HEADER=lem_in.h
LIB_DIR=libft

all: $(LIB) $(LEM_IN)

$(LEM_IN): $(OBJ) $(HEADER)
	gcc $(CC_FLAGS) -o $(LEM_IN) $(OBJ) $(LIB_DIR)/$(LIB)

$(LIB):
	make -C $(LIB_DIR)

%.o: %.c
	gcc -c $(CC_FLAGS) $< -o $@

clean:
	make -C $(LIB_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIB_DIR) fclean
	rm -f $(LEM_IN)

re: fclean all
