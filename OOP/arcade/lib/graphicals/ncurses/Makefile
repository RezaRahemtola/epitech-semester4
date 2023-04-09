##
## EPITECH PROJECT, 2023
## C++ Project
## File description:
## Makefile
##

BASE_DIR	=	.

FILES		=	Ncurses.cpp
SRC			=	$(addprefix $(BASE_DIR)/, $(FILES))
OBJ			=	$(SRC:.cpp=.o)

BINARY			=	../../arcade_ncurses.so

HEADERS_DIRS 	=	.

CXXFLAGS		=	-Wall -Wextra -std=c++20 -fPIC
CPPFLAGS		=	$(HEADERS_DIRS:%=-iquote %)

LDLIBS			=	-lncurses

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
