# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 19:10:36 by ldurante          #+#    #+#              #
#    Updated: 2022/10/24 01:07:59 by ldurante         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARIABLE DECLARATIONS #

NAME = containers
CXX = clang++
RM = rm -rf
# CXXFLAGS = -Wall -Wextra -Werror
EXTRAS = -std=c++98 -pedantic -g
		 -fsanitize=address

# COLORS #

RED = \033[0;31m
GREEN = \033[0;32m
GREY = \033[2;37m
MAGENTA = \033[0;35m
NO_COLOR = \033[0m

# SOURCES & OBJECTS #

# SRCS = main.cpp

SRCS = main_tests/main.cpp main_tests/vector.cpp
# SRCS = main_new.cpp

OBJS = $(SRCS:.cpp=.o)

# RULES #

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(EXTRAS) $(OBJS) -o $(NAME)
	@echo "$(GREY) $(NAME) compiled $(GREEN) ✔✔✔ $(NO_COLOR)"

clean:
	@clear
	@$(RM) $(OBJS)
	@$(RM) *.dSYM
	@echo "$(RED) **** object files removed **** $(NO_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED) **** $(NAME) removed **** $(NO_COLOR)"

re: fclean all

.PHONY: all re clean fclean

.SILENT: $(OBJS)