NAME = libasm.a

SRC = ft__strlen.s

OBJ = $(SRC:.s=.o)

all: $(NAME)

$(OBJ): $(SRC)
	nasm -f elf64 -o $(OBJ) $(SRC)

$(NAME): $(OBJ)
	ar src $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME) $(OBJ)

re: fclean all

test: all
	gcc -L. -lasm -o test test.c 
