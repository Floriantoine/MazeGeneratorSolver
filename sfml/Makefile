##
## EPITECH PROJECT, 2018
## DANTE_2018
## File description:
## Maze_Makefile
##

SRC			=	src/main.cpp	   		   \
				src/toolbox/randy.cpp    \
				src/Maze.cpp\

OBJ_SRC		=	$(SRC:.cpp=.o)

NAME		=	 Maze

CC			=	g++

override CXXFLAGS	+=	-Wall -Wextra -I ./include -lsfml-window -lsfml-system -lsfml-graphics -lsfml-audio


$(NAME): $(OBJ_SRC)
	@echo -e "\e[36;1m\nMAKE $(NAME)\n\e[0m"
	@$(CC) $(CXXFLAGS) $^ -o $@

all:$(NAME)

clean:
	@echo -e "\e[31;1mCLEANING OBJ: $(NAME)\e[0m"
	@rm -rf $(OBJ_SRC)

fclean: clean
	@echo -e "\033[31;1mCLEANING: $(NAME)\033[0m"
	@rm -f $(NAME) $(NAME_TESTS)

re:	fclean	all

.PHONY:	all	clean	fclean	re
