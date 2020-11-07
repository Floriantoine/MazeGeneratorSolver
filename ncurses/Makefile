##
## EPITECH PROJECT, 2018
## DANTE_2018
## File description:
## generator_Makefile
##

SRC			=	src/main.c	   		   \
				src/generator.c		   \
				src/check_pos.c		   \
				src/toolbox/print_map.c\
				src/toolbox/my_pustr.c \
				src/toolbox/randy.c    \
				src/take_pos/take_pos.c\
				src/solve.c\
				src/tools.c\
				src/maze.c\
				src/check_all.c\

OBJ_SRC		=	$(SRC:.c=.o)

NAME		=	 generator

CC			=	gcc

override CFLAGS	+=	-Wall -Wextra -Werror -I ./include -lncurses

$(NAME): $(OBJ_SRC)
	@echo -e "\e[36;1m\nMAKE $(NAME)\n\e[0m"
	@$(CC) $(CFLAGS) $^ -o $@

all:$(NAME)

clean:
	@echo -e "\e[31;1mCLEANING OBJ: $(NAME)\e[0m"
	@rm -rf $(OBJ_SRC)

fclean: clean
	@echo -e "\033[31;1mCLEANING: $(NAME)\033[0m"
	@rm -f $(NAME) $(NAME_TESTS)

re:	fclean	all

.PHONY:	all	clean	fclean	re
