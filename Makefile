NAME = libasm.a

FALGS = -Wall -Werror -Wextra
NASM_FLAG = -f macho64

SRC = ft__strlen.s

OBJ = $(SRC:.s=.o)

all: $(NAME)

$(OBJ): $(SRC)
	nasm -f elf64 -o $(OBJ) $(SRC)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME) $(OBJ)

re: fclean all

test: all
	gcc $(FLAGS) -L. -lasm -o test test.c
