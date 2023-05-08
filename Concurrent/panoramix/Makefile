##
## EPITECH PROJECT, 2023
## panoramix
## File description:
## Makefile
##

NAME		=	panoramix

SRC_DIR		=	src/
SRC_FILES	=	main.c \
				parsing.c \
				panoramix.c \

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ			=	$(SRC:.c=.o)

INC			=	include/

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror
CPPFLAGS	=	-iquote $(INC)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all


.PHONY: all re clean fclean
