##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC_DIR		=	src
SRC_FILES	=	strlen.asm \
				strchr.asm \
				strrchr.asm \
				memset.asm \
				memcpy.asm \
				strcmp.asm \
				memmove.asm \
				strncmp.asm \
				strcasecmp.asm \
				strstr.asm \
				strpbrk.asm \
				strcspn.asm \
				index.asm \
				rindex.asm
SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ			=	$(SRC:.asm=.o)

ASM		=	nasm
ASFLAGS	=	-f elf64
LD		=	ld
LDFLAGS	=	-shared
BINARY	=	libasm.so


CC			=	gcc

TESTS_DIR	=	tests
TESTS_SRC	=	main.c
TEST		=	$(addprefix $(TESTS_DIR)/, $(TESTS_SRC))
TEST_OBJ	=	$(TEST:.c=.o)
TEST_BINARY =	unit_tests


all: $(BINARY)

$(BINARY):	$(OBJ)
			$(LD) $(LDFLAGS) $(OBJ) -o $(BINARY)

$(TEST_BINARY): CPPFLAGS += -fno-builtin
$(TEST_BINARY):	all $(TEST_OBJ)
				@$(CC) -o $(TEST_BINARY) $(TEST_OBJ)
				@LD_PRELOAD=./$(BINARY) ./$(TEST_BINARY)

tests_run:	$(TEST_BINARY)

clean:
			$(RM) $(OBJ)
			$(RM) $(TEST_OBJ)

fclean:		clean
			$(RM) $(BINARY)

re: fclean all

%.o: %.asm
			$(ASM) $(ASFLAGS) -o $@ $<

.PHONY: all clean fclean re tests_run
