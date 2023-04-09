##
## EPITECH PROJECT, 2023
## C++ Project
## File description:
## Makefile
##

BASE_DIR	=	.

FILES		=	SDL2.cpp
SRC			=	$(addprefix $(BASE_DIR)/, $(FILES))
OBJ			=	$(SRC:.cpp=.o)

BINARY			=	../../arcade_sdl2.so

HEADERS_DIRS 	=	.

CXXFLAGS		=	-Wall -Wextra -std=c++20 -fPIC
CPPFLAGS		=	$(HEADERS_DIRS:%=-iquote %)

LDLIBS			=	-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx

CXX				=	g++

all:	$(BINARY)

$(BINARY):	$(OBJ)
			$(CXX) -shared -o $(BINARY) $(OBJ) $(LDLIBS)

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(BINARY)

re:	fclean all

.PHONY:	all	clean fclean re
