##
## EPITECH PROJECT, 2023
## nts
## File description:
## Makefile
##

HEADERS_DIR		=	include

SRC_DIR			=	src

PARSING_SRC		=	Parsing.cpp

SIMULATOR_SRC	=	Simulator.cpp

CMP_GATES_SRC	=	AGate.cpp \
					And.cpp \
					Or.cpp \
					Not.cpp \
					Xor.cpp \
					Nand.cpp \
					Nor.cpp

CMP_SPECIAL_SRC	=	Input.cpp \
					Clock.cpp \
					Output.cpp \
					True.cpp \
					False.cpp \
					AEntry.cpp

COMPONENTS_SRC	=	AComponent.cpp \
					Factory.cpp \
					$(addprefix gates/, $(CMP_GATES_SRC)) \
					$(addprefix special/, $(CMP_SPECIAL_SRC)) \
					$(addprefix circuits/, $(CIRCUITS_SRC))

CIRCUITS_SRC	=	Circuit.cpp \
					GatesCircuit.cpp \
					Circuit4069.cpp

BASE_SRC		=	$(addprefix parsing/, $(PARSING_SRC)) \
					$(addprefix simulator/, $(SIMULATOR_SRC)) \
					$(addprefix components/, $(COMPONENTS_SRC))

SRC				=	$(addprefix $(SRC_DIR)/, $(BASE_SRC))
MAIN			=	$(SRC_DIR)/Main.cpp

OBJ				=	$(SRC:.cpp=.o) $(MAIN:.cpp=.o)

TST_DIR			=	tests
TST				=
TST_OBJ			=	$(SRC:.cpp=.o) $(TST:.cpp=.o)
LIBS 			=

BINARY			=	nanotekspice
TST_BINARY		= 	$(BINARY).test
DEBUG_BINARY	=	$(BINARY).debug

CPPFLAGS 		+= 	-Wall -Wextra -iquote $(HEADERS_DIR) -std=c++20
CXXFLAGS		+=
LDLIBS			+= 	$(addprefix -l, $(LIBS))

CXX				= g++

# Build targets:

all: $(BINARY)

$(BINARY): $(OBJ)
	$(CXX) $(OBJ) -o $(BINARY) $(LDLIBS)

$(TST_BINARY): LIBS		+=	criterion gcov
$(TST_BINARY): CPPFLAGS 	+=	-ftest-coverage -fprofile-arcs
$(TST_BINARY): $(TST_OBJ)
	$(CXX) $(TST_OBJ) -o $(TST_BINARY) $(LDLIBS)

$(DEBUG_BINARY): CXXFLAGS +=	-g
$(DEBUG_BINARY): $(OBJ)
	$(CXX) $(OBJ) -o $(DEBUG_BINARY) $(LDLIBS)

re:	fclean all

# Other targets:

tests_run: $(TST_BINARY)
	./$(TST_BINARY)
	gcovr --exclude $(TST_DIR)
	gcovr --exclude $(TST_DIR) --branches

debug: re $(DEBUG_BINARY)

# Cleaning targets:

clean:
	$(RM) $(OBJ) $(TST_OBJ)

fclean: clean
	$(RM) $(BINARY) $(TST_BINARY) $(DEBUG_BINARY)

.PHONY: all clean fclean tests_run re debug
