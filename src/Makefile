CC = g++
FLAGS = -Wall -Wextra -Werror -std=c++17
NAME = Engine

all: clean build

build:
	@$(CC) $(FLAGS) $(NAME).cpp -o $(NAME)
	@./$(NAME)

clean:
	@rm -f $(NAME)