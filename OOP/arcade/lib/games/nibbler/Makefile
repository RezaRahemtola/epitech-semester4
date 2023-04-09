##
## EPITECH PROJECT, 2023
## C++ Project
## File description:
## Makefile
##

BASE_DIR	=	.

FILES		=	Nibbler.cpp
SRC			=	$(addprefix $(BASE_DIR)/, $(FILES)) \
				../AGameModule.cpp
OBJ			=	$(SRC:.cpp=.o)

BINARY			=	../../arcade_nibbler.so

HEADERS_DIRS 	=	.

CXXFLAGS		=	-Wall -Wextra -std=c++20 -fPIC
CPPFLAGS		=	$(HEADERS_DIRS:%=-iquote %)

CXX				=	g++

all:	$(BINARY)

$(BINARY):	$(OBJ)
			$(CXX) -shared -o $(BINARY) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(BINARY)

re:	fclean all

.PHONY:	all	clean fclean re
