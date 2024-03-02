NAME = petra

### SRCS ################################################################

SRCS = 	./engine/base/src/*.cpp \
		./engine/core/src/*.cpp \
		./engine/maths/src/*.cpp \
		./engine/rendering/src/*.cpp \
		./engine/utils/src/*.cpp \

CSRCS = ./engine/C/src/*.c \
		./engine/utils/src/*.c \
		./thirdparty/glad/glad.c \

### OBJS ################################################################

PATH_O = debug/

OBJS = $(SRCS:.cpp=.o)

COBJS = $(CSRCS:.c=.o)

### INCLUDES ############################################################

INCLUDES = -Iengine/ -Ithirdparty/

### COMPILATION ##########################################################

CC = gcc
CXX = g++ -std=c++2a

LIBS = -Lthirdparty/libs

DEBUG = -O0
BBUILD = -Ofast -finline-functions -funroll-all-loops -flto -Bsymbolic -fexpensive-optimizations -ffast-math -funsafe-math-optimizations -freorder-functions -ftree-vectorize

FLAGS = -Wall -Wextra -fexceptions -lgdi32 -luser32 -lkernel32 -lopengl32 -lmingw32 -lglfw3dll -lm -lz
ifeq ($(build), 1)
FLAGS += $(BBUILD)
else
FLAGS += $(DEBUG)
endif

CFLAGS = $(FLAGS)
CXXFLAGS = $(FLAGS)

### RULES ################################################################

$(COBJS): $(CSRCS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(PATH_O)$^

$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(PATH_O)$^

$(NAME): $(COBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(addprefix $(PATH_O), $^) -o $@

all: $(NAME)

clean:
	del *.o

fclean: clean
	del $(NAME)

re: fclean all