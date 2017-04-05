# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/27 14:59:24 by mdufaud           #+#    #+#              #
#    Updated: 2016/02/16 15:42:32 by rcherik          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := $(shell uname)

ifeq ($(OS),Linux)
SHELL := /bin/bash
ECHO := echo -e
else
SHELL := /bin/sh
ECHO := echo
endif

NAME = n_puzzle
CFLAGS = g++ -Wall -Werror -Wextra -o3 -g
LFLAGS = -lncurses
OFLAGS = -I ./includes/.
PATH_SRC = srcs
PATH_OBJ = obj
SRC = main.cpp\
	  printPuzzle.cpp\
	  Puzzle.class.cpp\
	  generateSnail.cpp\
	  Map.class.cpp\
	  parseArgs.cpp\
	  error.cpp\
	  split.cpp\
	  numsize.cpp\
	  Node.class.cpp\
	  flatten.cpp\
	  algo.cpp

OBJ = $(patsubst %.cpp, $(PATH_OBJ)/%.o, $(SRC))

INCLUDES = includes/Puzzle.class.hpp\
		   includes/n_puzzle.hpp\
		   includes/Map.class.hpp\
		   includes/Node.class.hpp

all : $(NAME)

$(PATH_OBJ)/%.o : $(addprefix $(PATH_SRC)/, %.cpp) $(INCLUDES)
	@mkdir -p $(PATH_OBJ)
	@$(CFLAGS) $(OFLAGS) -o $@ -c $<

$(NAME) : $(OBJ)
	@$(ECHO) "\033[32m[ $(NAME) objects done ]\033[00m"
	@$(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)
	@$(ECHO) "\033[32m[ $(NAME) compiled ]\033[00m"

clean :
	@rm -f $(OBJ)
	@rm -rf $(NAME).dSYM
	@rm -rf $(PATH_OBJ)
	@$(ECHO) "\033[31m[ $(NAME) : objects deleted ]\033[00m"

fclean : clean
	@rm -f $(NAME)
	@$(ECHO) "\033[31m[ $(NAME) : ./$(NAME) deleted ]\033[00m"

re : fclean all

.PHONY : fclean re clean all
