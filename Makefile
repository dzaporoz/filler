# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/08 17:43:10 by dzaporoz          #+#    #+#              #
#    Updated: 2018/12/08 18:15:14 by dzaporoz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = dzaporoz.filler

BONUS = vizualizator

SRC = ./filler/main.c ./filler/strategy.c ./filler/data_reading.c 

OBJ = ./main.o ./strategy.o ./data_reading.o

BONUS_SRC = ./visualisation/visualize.c ./visualisation/print_board.c

BONUS_OBJ = ./visualize.o ./print_board.o

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	make -C libft
	gcc -c $(FLAGS) $(SRC) $(BONUS_SRC)
	gcc -o $(BONUS) $(FLAGS) $(BONUS_OBJ) -I ./visualisation  libft/libft.a
	gcc -o $(NAME) $(FLAGS) $(OBJ) -I ./filler libft/libft.a
	echo "Filler done"

clean:
	make clean -C libft
	rm -f $(BONUS_OBJ)
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(BONUS)
	rm -f $(NAME)

re: fclean all
