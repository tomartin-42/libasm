NAME = libasm.a

CFLAGS = -Wall -Werror -Wextra

UNAME := $(shell uname)


ifeq ($(UNAME), Darwin)
	NASM_FLAG = -f macho64
	SRC_DIR = ./mac
else
	NASM_FLAG = -f elf64
	SRC_DIR = ./linux
endif


SRC_FILES = ft__strlen.s ft__strcmp.s ft__strcpy.s ft__strdup.s ft__read.s ft__write.s 
BONUS_FILES = ft__atoi_base.s
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
SRC_BONUS = $(addprefix $(SRC_DIR)/, $(BONUS_FILES))
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.s=.o))

ifdef BONUS
    SRC += $(SRC_BONUS)
    OBJ += $(addprefix $(OBJ_DIR)/, $(BONUS_FILES:.s=.o))
endif

all: $(NAME) 
	@echo "██╗     ██╗██████╗  █████╗ ███████╗███╗   ███╗"
	@echo "██║     ██║██╔══██╗██╔══██╗██╔════╝████╗ ████║"
	@echo "██║     ██║██████╔╝███████║███████╗██╔████╔██║"
	@echo "██║     ██║██╔══██╗██╔══██║╚════██║██║╚██╔╝██║"
	@echo "███████╗██║██████╔╝██║  ██║███████║██║ ╚═╝ ██║"
	@echo "╚══════╝╚═╝╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝"
	@echo "By Tomartin in 42Madrid"
	@echo "compiling libasm.a"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(OBJ_DIR)
	nasm -f elf64 -o $@ $< -g -l $(OBJ_DIR)/$*.lst


$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: 
	@make BONUS=1

clean:
	rm -f $(OBJ)
	@echo "Clean .o!!"

fclean:
	rm -Rf $(OBJ_DIR)
	rm -f $(NAME) 
	rm -f *.lst
	rm -f test
	@echo "All clean!!"

re: fclean all

test:
	gcc -no-pie $(CFLAGS) -g3 -o test test.c ft_atoi_base.c -L. -lasm
	#./test

print:
	@echo $(SRC)
	@echo $(SRC_FILES)
	@echo $(SRC_DIR)
	@echo $(OBJ)

print_bonus:
	@make BONUS=1
	@echo $(SRC)
	@echo $(SRC_FILES)
	@echo $(SRC_DIR)
	@echo $(OBJ)

a: fclean bonus test
