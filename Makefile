Creator:Creator.c
	gcc -o Creator Creator.c
printable_shellcode:printable_shellcode.o
	ld -o printable_shellcode printable_shellcode.o
printable_shellcode.o:printable_shellcode.asm
	nasm -f elf printable_shellcode.asm
clean:
	rm ./Creator
	rm ./shellcode.o
	rm ./shellcode
