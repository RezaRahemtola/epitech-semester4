##
## EPITECH PROJECT, 2023
## Haskell template
## File description:
## Makefile
##

NAME		=	imageCompressor

BINARY_PATH =	$(shell stack path --local-install-root)

all: $(NAME)

$(NAME):
		stack build
		cp $(BINARY_PATH)/bin/$(NAME)-exe ./$(NAME)

clean:
		stack clean

fclean: clean
		$(RM) $(NAME)

tests_run:
		stack test --coverage

re:		fclean all

.PHONY: all clean fclean tests_run re
