NAME = libasm.a

FALGS = -Wall -Werror -Wextra

ifeq ($(UNAME), Darwin)
	NASM_FLAG = -f macho64
else
	NASM_FLAG = -f elf64
endif

SRC = ft__strlen.s ft__strcmp.s ft__strcpy.s

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.s=.o))

all: $(NAME) 
	@echo "compiling libasm.a"

$(OBJ_DIR)/%.o: %.s
	@mkdir -p $(OBJ_DIR)
	nasm -f elf64 -o $@ $< -g -l $*.lst

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:
	rm -Rf $(OBJ_DIR)
	rm -f $(NAME) 
	rm -f *.lst
	rm -f test
	@echo "All clean!!"

re: fclean all

test: all
	gcc $(FLAGS) -g3 -o test test.c -L. -lasm 
	./test 
