NAME = libasm.a

CFLAGS = -fsanitize=address -Wall -Werror -Wextra

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	NASM_FLAG = -f macho64
	SRC_DIR = ./mac
	VER = "MAC VERSIOM"
	ASM_FLAG = macho64
	NO_PIE = ''
else
	NASM_FLAG = -f elf64
	SRC_DIR = ./linux
	VER = "LINUX VERSIOM"
	ASM_FLAG = elf64
	NO_PIE = -no-pie
endif

SRC_FILES = ft_strlen.s ft_strcmp.s ft_strcpy.s ft_strdup.s ft_read.s ft_write.s 
BONUS_FILES = ft_atoi_base.s ft_atoi_base_test.s ft_list_size.s ft_list_push_front.s \
							ft_list_sort.s ft_list_remove_if.s
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
SRC_BONUS = $(addprefix $(SRC_DIR)/, $(BONUS_FILES))
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.s=.o))

ifdef BONUS 
    SRC += $(SRC_BONUS)
    OBJ += $(addprefix $(OBJ_DIR)/, $(BONUS_FILES:.s=.o))
endif

all: $(NAME) 
	@echo $(VER)
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
	nasm -f $(ASM_FLAG) -o $@ $< -g -l $(OBJ_DIR)/$*.lst

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
	rm -f ./test
	rm -f ./test_bonus
	@echo "All clean!!"

re: fclean all

test: all
	gcc $(NO_PIE) $(CFLAGS) -g3 -o ./test test.c -L. -lasm && ./test 

test_bonus: bonus
	gcc $(NO_PIE) $(CFLAGS) -g3 -o ./test_bonus test_bonus.c -L. -lasm && ./test_bonus 

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

