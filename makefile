ft__strlen: ft__strlen.o
	gcc -o ft__strlen ft__strlen.o -no-pie

ft__strlen.o: ft__strlen.asm
	nasm -f elf64 -g -F dwarf ft__strlen.asm -l ft__strlen.lst
