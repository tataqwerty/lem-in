# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/14 15:41:10 by tkiselev          #+#    #+#              #
#    Updated: 2018/11/05 13:32:50 by tkiselev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
NAME=lem-in
LIB=libftprintf.a
LIB_DIR=libft/
CC_FLAGS=-Wall -Wextra -Werror

SRC_DIR=src/
SRC_NAMES=algorithm.c\
		   generate_ways.c\
		   is_functions.c\
		   links.c\
		   main.c\
		   output.c\
		   parsing.c\
		   rooms.c\
		   staff.c
SRC=$(addprefix $(SRC_DIR),$(SRC_NAMES))

OBJ_DIR=obj/
OBJ=$(addprefix $(OBJ_DIR), $(SRC_NAMES:.c=.o))

INC_DIR=inc/
INC=lem_in.h

all: $(NAME)

$(NAME): $(OBJ) $(LIB_DIR)$(LIB)
	$(CC) $(OBJ) -o $(NAME) $(LIB_DIR)$(LIB)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)$(INC)
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CC_FLAGS) $< -o $@ -I $(INC_DIR) -I $(LIB_DIR)

$(LIB_DIR)$(LIB):
	make -C $(LIB_DIR)

clean:
	make -C $(LIB_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(LIB_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
