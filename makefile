CXX      = g++

C_SRCS        = engine/C/src/*.c
CXX_SRCS      = main.cpp 	engine/base/src/*.cpp	engine/core/src/*.cpp	engine/maths/src/*.cpp	engine/rendering/src/*.cpp

STDCXX   = -std=c++17

IGLAD    = thirdparty/glad/glad.c
IFLAGS   = -Ithirdparty -Iengine

LIBS     = -Lthirdparty/libs
CFLAGS   = -Wall -fexceptions -lgdi32 -luser32 -lkernel32 -lopengl32 -lmingw32 -lglfw3dll -lm

DEBUG    = #-O0 -pg
BUILD    = -O3 -finline-functions -funroll-loops -fprofile-generate
BBUILD   = -Ofast -finline-functions -funroll-all-loops -flto -Bsymbolic -fexpensive-optimizations -ffast-math -funsafe-math-optimizations -freorder-functions -ftree-vectorize
 
compile:
	$(CXX) $(DEBUG) $(C_SRCS) $(CXX_SRCS) $(STDCXX) $(IGLAD) $(IFLAGS) $(LIBS) $(CFLAGS) -o petra.exe

compile_and_launch:compile 
			       petra.exe
l:
	./petra.exe
c:compile
re:compile_and_launch

build:
	$(CXX) $(BBUILD) $(C_SRCS) $(CXX_SRCS) $(STDCXX) $(IGLAD) $(IFLAGS) $(LIBS) $(CFLAGS) -o petra.exe