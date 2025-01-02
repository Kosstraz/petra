# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bama <bama@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 16:21:19 by ymanchon          #+#    #+#              #
#    Updated: 2025/01/02 20:58:30 by bama             ###   ########.fr        #
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

NAME = petra

CXX = @c++ -std=c++20

SRCS =	./Scripts/*.cpp \
		./main.cpp

LMAKE = @make --no-print-directory -C

OBJS_DIR = .objs

OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.obj)

DEPS = $(OBJS:%.obj=%.d)

INCLUDES = -I . -I ./Helper/includes/ -I ./Engine/includes/ -I ./LesJardinsSuspendus/includes/ -I ./Scripts/

OPTIFLAGS =	-Ofast -march=native -mtune=generic -funroll-loops -fomit-frame-pointer -ffast-math

CFLAGS = -Wall -Wextra -Wshadow -Wuninitialized -Wno-unused-result -Winit-self -MMD $(OPTIFLAGS) -fPIE -g3 #-Werror

LIB = -L ./Engine/ -L ./Helper -L ./LesJardinsSuspendus/ 

EXTERN_LIB = -lpetrajardinssuspendus -lpetrahelper -lpetra -lnsl -lglfw

ALL_LIB = $(LIB) $(EXTERN_LIB)

LIB_PETRA_PATH = ./Engine/libpetra.a
LIB_JARSU_PATH = ./LesJardinsSuspendus/libpetrajardinssuspendus.a
LIB_HELPE_PATH = ./Helper/libpetrahelper.a
LIBS_PATH = $(LIB_PETRA_PATH) $(LIB_JARSU_PATH) $(LIB_HELPE_PATH)

# ############## #
#*    REGLES    *#
# ############## #

all: compile_petra_libs check_compilation $(NAME)

fre:
	$(LMAKE) ./Helper/ re
	$(LMAKE) ./Engine/ re
	$(LMAKE) ./LesJardinsSuspendus/ re
	$(LMAKE) . that

compile_petra_libs:
	$(LMAKE) ./Helper/
	$(LMAKE) ./Engine/
	$(LMAKE) ./LesJardinsSuspendus/

that: check_compilation $(NAME)

check_compilation:
	@if [ -f $(NAME) ] && \
		[ -n "$(strip $(OBJS))" ] && \
		[ -n "$(strip $(EXTERN_LIB))" ] && \
		[ -z "$$(find $(SRCS) -newer $(NAME) 2>/dev/null)" ] && \
		[ ! $(LIB_PETRA_PATH) -nt $(NAME) ] && \
		[ ! $(LIB_JARSU_PATH) -nt $(NAME) ] && \
		[ ! $(LIB_HELPE_PATH) -nt $(NAME) ]; then \
		echo "$(BOLD)$(PURPLE)Tous les fichiers $(UNDERLINE)$(YELLOW)$(NAME)$(CLASSIC)$(BOLD)$(PURPLE) sont déjà compilés !$(CLASSIC)"; \
		exit 0; \
	fi

$(NAME): $(OBJS) $(LIBS_PATH)
	$(CXX) $(CFLAGS) $(OBJS) $(LIB) $(EXTERN_LIB) -o $@
	@echo "$(BOLD)$(CYAN)Exécutable $(NAME) créé avec succès!$(CLASSIC)"

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

.PHONY: all that check_compilation compile_petra_libs clean fclean re fre
-include $(DEPS)

# ############## #
#*    AUTRES    *#
# ############## #
