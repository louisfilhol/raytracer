##
## EPITECH PROJECT, 2025
## bootstrap [WSL: Ubuntu-24.04]
## File description:
## Makefile
##

CC = g++
CFLAGS = -std=c++20 -Wall -Wextra -lpthread

NAME = raytracer

SRC = $(shell find . -name "*.cpp")

OBJ = $(SRC:.cpp=.o)

INCLUDES = -I./

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -lsfml-graphics -lsfml-window -lsfml-system -lconfig++

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME)_output.ppm

re: fclean all

debug: CFLAGS += -g3 -O0
debug: re

.PHONY: all clean fclean re debug