BIN=test
SRCDIR=src/
OBJDIR=obj/
BINDIR=bin/
SRCS=$(wildcard $(SRCDIR)*.cpp)
OBJS=$(addprefix $(OBJDIR),$(notdir $(SRCS:.cpp=.o)))
CXX=g++
CFLAGS=-std=c++17 -Wall -Wextra -pedantic-errors
# Linux
#IFLAGS=-Iinclude/ -I/usr/include
#LIBFLAGS= `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
# Mac (assumes SDL installed via brew)
IFLAGS=-Iinclude/ -I/usr/Local/Cellar/sdl2/2.0.14_1/include/SDL2 -I/usr/Local/Cellar/sdl2_image/2.0.5/include/SDL2
LIBFLAGS=-lSDL2-2.0.0 -lSDL2_image-2.0.0


all: $(SRCS) $(BINDIR)$(BIN)
$(BINDIR)$(BIN): $(OBJS) | bin
	$(CXX) $(OBJS) $(LIBFLAGS) -o $@
$(OBJS): $(OBJDIR)%.o: $(SRCDIR)%.cpp | obj
# Linux
#	$(CXX) -c $(CFLAGS) $(IFLAGS) $(LIBFLAGS) $< -o $@
# Mac
	$(CXX) -c $(CFLAGS) $(IFLAGS) $< -o $@

obj:
	mkdir -p $@

bin:
	mkdir -p $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)