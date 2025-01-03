# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bama <bama@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 16:21:19 by ymanchon          #+#    #+#              #
#    Updated: 2025/01/04 00:12:51 by bama             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ################ #
#*    COULEURS    *#
# ################ #

CLASSIC	= \e[0m
WHITE	= \e[38;2;238;232;213m
BOLD	= \e[1m
UNDERLINE	= \e[4m
# BLACK	= \e[38;2;0;0;0m
BLACK	= \e[30m
RED   	= \e[31m
GREEN  	= \e[32m
BLUE 	= \e[38;2;0;36;148m
PURPLE 	= \e[38;2;211;54;130m
CYAN   	= \e[36m
YELLOW 	= \e[38;2;250;189;0m

# ############### #
#*   VARIABLES   *#
# ############### #

NAME = libpetra.a

CXX = @c++ -std=c++20

AR = @ar -rcs

SRCS =	./src/Engine.cpp			\
		./src/TestsLoop.cpp			\

LMAKE = @make --no-print-directory -C

OBJS_DIR = .objs

OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.obj)

DEPS = $(OBJS:%.obj=%.d)

INCLUDES = -I . -I ./includes/ -I ../Gestalt/

OPTIFLAGS =	-Ofast -march=native -mtune=generic -funroll-loops -fomit-frame-pointer -ffast-math

CFLAGS = -Wall -Wextra -Wshadow -Wuninitialized -Wno-unused-result -Winit-self -MMD $(OPTIFLAGS) -fPIE -g3 #-Werror

LIB =

EXTERN_LIB =

ALL_LIB = $(LIB) $(EXTERN_LIB)

# ############## #
#*    REGLES    *#
# ############## #

all: check_compilation $(NAME)

check_compilation:
	@if [ -f $(NAME) ] && [ -n "$(strip $(OBJS))" ] && [ -z "$$(find $(SRCS) -newer $(NAME) 2>/dev/null)" ]; then \
		echo "$(BOLD)$(PURPLE)Tous les fichiers $(UNDERLINE)$(YELLOW)$(NAME)$(CLASSIC)$(BOLD)$(PURPLE) sont déjà compilés !$(CLASSIC)"; \
		exit 0; \
	fi

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)
	@echo "$(BOLD)$(CYAN)Librairie $(NAME) créé avec succès!$(CLASSIC)"

$(OBJS_DIR)/%.obj: %.cpp
	@mkdir -p $(@D)
	@echo "$(GREEN)🗸 Compilation $(BOLD)$(YELLOW)$<$(CLASSIC)"
	$(CXX) $(INCLUDES) $(CFLAGS) $(ALL_LIB) -c $< -o $@

clean:
	@echo "$(BOLD)$(RED)"
	rm $(LIBFT_P)/$(OBJS_DIR) -rf
	rm $(OBJS_DIR) -rf
	@echo "$(CLASSIC)"

fclean: clean
	@echo "$(BOLD)$(RED)"
	rm $(NAME) -f
	@echo "$(BOLD)$(GREEN)Tout a été supprimé... 🗑️\n$(CLASSIC)"

re: fclean all

.PHONY: all check_compilation clean fclean re
-include $(DEPS)

# ############## #
#*    AUTRES    *#
# ############## #
