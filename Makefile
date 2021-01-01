# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laskolin <laskolin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/09 08:30:56 by laskolin          #+#    #+#              #
#    Updated: 2020/03/09 10:17:54 by laskolin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

LIBMLX = ./lib/libmlx

LIBFT = ./lib/libft

SRC = main.c parts.c help.c maze.c img_reader.c wimg_reader.c ray.c ray2.c \
	wall.c wall2.c shader.c key.c actions.c shoot.c move.c move2.c color.c 

OBJ = $(subst .c,.o,$(SRC))

MLXFLAGS = -I$(LIBMLX) -L$(LIBMLX) -lmlx -framework OpenGL -framework Appkit

LIBFTFLAGS = -L$(LIBFT) -lft

FLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):
	make -C $(LIBFT)/
	make -C $(LIBMLX)/
	gcc $(FLAGS) -I libft/ -c $(SRC) 
	gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIBFTFLAGS) $(MLXFLAGS)

clean:
	/bin/rm -f $(OBJ)
	make clean -C $(LIBFT)/

fclean: clean
	make fclean -C $(LIBFT)/
	/bin/rm -f $(NAME)

re: fclean all
