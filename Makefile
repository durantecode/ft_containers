# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 19:10:36 by ldurante          #+#    #+#              #
#    Updated: 2022/11/04 20:56:23 by ldurante         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARIABLE DECLARATIONS #

NAME = containers
CXX = clang++
RM = rm -rf
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic -g3

# COLORS #

RED = \033[0;31m
GREEN = \033[0;32m
GREY = \033[2;37m
MAGENTA = \033[0;35m
NO_COLOR = \033[0m

# SOURCES & OBJECTS #

# SRCS = main.cpp

SRCS =  main_tests/main.cpp \
		main_tests/vector_tests.cpp \
		main_tests/vector_time_tests.cpp \
		main_tests/stack_tests.cpp \
		main_tests/stack_time_tests.cpp \
		main_tests/print_and_comparision.cpp \
		main_tests/utility_tests.cpp \
		# main_tests/map_tests.cpp \
		# main_tests/map_time_tests.cpp \

# SRCS = main_new.cpp

OBJS = $(SRCS:.cpp=.o)

# RULES #

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREY) $(NAME) compiled $(GREEN) ✔✔✔ $(NO_COLOR)"

leaks:
	valgrind --leak-check=full ./containers all

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