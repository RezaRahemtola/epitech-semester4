##
## EPITECH PROJECT, 2023
## C++ Project
## File description:
## Makefile
##

BASE_DIR		=	src
FILES			=	Main.cpp \
					Core.cpp \
					Parsing.cpp
SRC				=	$(addprefix $(BASE_DIR)/, $(FILES))
OBJ				=	$(SRC:.cpp=.o)

BINARY			=	arcade

HEADERS_DIRS 	=	include
CXXFLAGS		=	-Wall -Wextra -std=c++20 -fno-gnu-unique
LDFLAGS			=	-ldl
CPPFLAGS		=	$(HEADERS_DIRS:%=-iquote %)
CXX				=	g++


GRAPHICAL_LIBS	=	./lib/graphicals/ncurses 	\
					./lib/graphicals/sfml		\
					./lib/graphicals/sdl2		\

GAME_LIBS		=	./lib/games/snake			\
					./lib/games/nibbler			\


all:	core graphicals games

core:	$(OBJ)
		$(CXX) -o $(BINARY) $(OBJ) $(LDFLAGS)

graphicals:
		$(foreach lib, $(GRAPHICAL_LIBS), make -C $(lib);)

games:
		$(foreach lib, $(GAME_LIBS), make -C $(lib);)

clean:
		$(RM) $(OBJ)
		$(foreach lib, $(GRAPHICAL_LIBS), make clean -C $(lib);)
		$(foreach lib, $(GAME_LIBS), make clean -C $(lib);)

fclean:	clean
		$(RM) $(BINARY)
		$(foreach lib, $(GRAPHICAL_LIBS), make fclean -C $(lib);)
		$(foreach lib, $(GAME_LIBS), make fclean -C $(lib);)

re:	fclean all

.PHONY:	all	clean fclean re core graphicals games
