NAME = libasm.a

FALGS = -Wall -Werror -Wextra
NASM_FLAG = -f macho64

SRC = ft__strlen.s ft__strcmp.s

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.s=.o))

all: $(NAME) 

$(OBJ_DIR)/%.o: %.s
	mkdir -p $(OBJ_DIR)
	nasm -f elf64 -o $@ $< -g -l $*.lst

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:
	rm -Rf $(OBJ_DIR)
	rm -f $(NAME) 
	rm *.lst
	rm test

re: fclean all

test: all
	gcc $(FLAGS) -o test test.c -L. -lasm 
	./test 
