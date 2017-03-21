Creator:Creator.c
	gcc -o Creator Creator.c
shellcode:shellcode.o
	ld -o shellcode shellcode.o
shellcode.o:shellcode.asm
	nasm -f elf shellcode.asm
encrypt:encrypt.c
	gcc -o encrypt encrypt.c
clean:
	rm ./Creator
	rm ./shellcode.o
	rm ./shellcode
