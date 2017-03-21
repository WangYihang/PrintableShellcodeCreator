/* ================================================================================
 *  The MIT License
 * 
 *  Copyright (c) <year> <copyright holders>
 * 
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 * ================================================================================
 *  Author : WangYihang
 *  Email : wangyihanger@gmail.com
 *  Tested on: Linux_x86
 * ================================================================================
 *  Github URL : https://coding.net/u/yihangwang/p/PrintableShellcodeCreator/git 
 *  THe code can improve a lot of places , I finished it in a hurry , and I will impove in the futue
 *  The printable shellcode will be smaller then , and will support more platfroms.
 * ================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct RESULT_BYTE {
		int overflow; // 进位的个数
		unsigned char a;
		unsigned char b;
		unsigned char c;
};

struct RESULT{
		int result_a;
		int result_b;
		int result_c;
};

unsigned char *getMAX(unsigned char *a, unsigned char *b, unsigned char *c);
unsigned char *getMIN(unsigned char *a, unsigned char *b, unsigned char *c);
struct RESULT_BYTE * searchByte(unsigned char target, unsigned char start);
struct RESULT * search(int target, char start);
unsigned char * build(char * shellcode, char start);
void showHelp(char *filename);
void setZero();
void printNOP();
void printComment(int target);
void printAddESP();
void printHex(char *shellcode);

int main(int argc, char *argv[]){
		if (argc != 2){
				showHelp(argv[0]);
				exit(1);
		}
		char *filename = argv[1];
		char shellcode[4096] = {0};
		FILE *file = fopen(filename, "r");
		fread(shellcode, 1, 4096, file);
		fclose(file);
		printf("[SHELLCODE_FILE_NAME] : [%s]\n", filename);
		printf("[SHELLCODE] : ");
		printHex(shellcode);
		printf("[SHELLCODE_LENGTH] : %d\n", strlen(shellcode));
		build(shellcode, 0x20);
		return 0;
}

void printHex(char *shellcode){
		while (*shellcode){
				printf("%c", *shellcode++); 
		}
		printf("\n");
}

unsigned char *getMAX(unsigned char *a, unsigned char *b, unsigned char *c){
		unsigned char *MAX = a;
		if (*b > *MAX){
				MAX = b;
		}
		if (*c > *MAX){
				MAX = c;
		}
		return MAX;
}

unsigned char *getMIN(unsigned char *a, unsigned char *b, unsigned char *c){
		unsigned char *MIN = a;
		if (*b < *MIN){
				MIN = b;
		}
		if (*c < *MIN){
				MIN = c;
		}
		return MIN;
}

struct RESULT_BYTE * searchByte(unsigned char target, unsigned char start){
		unsigned char a = start;
		unsigned char b = start;
		unsigned char c = start;

		int counter = 0;

		while(counter++ < 0xFF){
				unsigned char temp = (a + b + c); // 计算和
				unsigned char *pointer;
				if (temp > target){
						pointer = getMAX(&a, &b, &c);	
						*pointer = *pointer - 1;
				}else if(temp < target){
						pointer = getMIN(&a, &b, &c);	
						*pointer = *pointer + 1;
				}else{
						if (a < start || b < start || c < start){
								a += 85;
								b += 85;
								c += 86;
						}
						struct RESULT_BYTE * result = malloc(sizeof(struct RESULT_BYTE));
						memset(result, 0, sizeof(struct RESULT_BYTE));
						result->a = a;
						result->b = b;
						result->c = c;
						int temp = a + b + c;
						result->overflow = temp / 0x100;
						return result;
				}
		}
}

struct RESULT * search(int target, char start){

		struct RESULT * result = malloc(sizeof(struct RESULT));
		memset(result, 0, sizeof(struct RESULT));
		unsigned char byte_l = (target >> 0) % 0x100;
		unsigned char byte_ml = (target >> 8) % 0x100;
		unsigned char byte_mh = (target >> 16) % 0x100;
		unsigned char byte_h = (target >> 24) % 0x100;
		int overflow = 0;

		struct RESULT_BYTE * result_byte = NULL;
		/**/
		result_byte = searchByte(byte_l, start);
		result->result_a = result->result_a + result_byte->a;//
		result->result_b = result->result_b + result_byte->b;//
		result->result_c = result->result_c + result_byte->c;//
		overflow = result_byte->overflow;
		free(result_byte);
		/**/
		result_byte = searchByte(byte_ml - overflow, start);
		result->result_a = result->result_a + result_byte->a * 0x100;//
		result->result_b = result->result_b + result_byte->b * 0x100;//
		result->result_c = result->result_c + result_byte->c * 0x100;//
		overflow = result_byte->overflow;
		free(result_byte);
		/**/
		result_byte = searchByte(byte_mh - overflow, start);
		result->result_a = result->result_a + result_byte->a * 0x10000;//
		result->result_b = result->result_b + result_byte->b * 0x10000;//
		result->result_c = result->result_c + result_byte->c * 0x10000;//
		overflow = result_byte->overflow;
		free(result_byte);
		/**/
		result_byte = searchByte(byte_h - overflow, start);
		result->result_a = result->result_a + result_byte->a * 0x1000000;//
		result->result_b = result->result_b + result_byte->b * 0x1000000;//
		result->result_c = result->result_c + result_byte->c * 0x1000000;//
		overflow = result_byte->overflow;
		free(result_byte);
		return result;
}

void setZero(){
		printf("\t\tand eax, 49494949H\n");
		printf("\t\tand eax, 30303030H\n");
}

void printComment(int target){
		printf("\t\t;========================\n");
		printf("\t\t;  set $eax=0x%x\n", target);
		printf("\t\t;========================\n");
}

void printHeader(){
		printf("global _start\n");
		printf("\t_start:\n");
}

void printNOP(int times){
		printf("\t\t;========================\n");
		printf("\t\t;  push 0x90\n");
		printf("\t\t;========================\n");
		int i = 0;
		for (i = 0; i < times; i++){
				printf("\t\tpush eax\n");
		}
}

void printAddESP(){
		printf("\t\t;========================\n");
		printf("\t\t;  add esp, ??? \n");
		printf("\t\t;========================\n");
		printf("\t\tpush esp\n");	
		printf("\t\tpop eax\n");	
		printf("\t\tsub eax, 55555442H\n");	
		printf("\t\tsub eax, 55555442H\n");	
		printf("\t\tsub eax, 55555442H\n");	
		printf("\t\tpush eax\n");	
		printf("\t\tpop esp\n");	
}

unsigned char * build(char * shellcode, char start){
		printHeader();
		printAddESP();

		int length_shellcode = strlen(shellcode);
		int length_malloc = (length_shellcode / 4 + 1 + 1) * 4;
		char * pointer = malloc(length_malloc);
		memset(pointer, 0x90, length_malloc);
		int i = 0;
		for (i = 0; i < length_shellcode; i++){
				pointer[i] = shellcode[i];
		}
		int *target = ((int *)pointer) + ((length_malloc) / 4 - 1);
		for (i = 0; i < (length_malloc / 4); i++){
				struct RESULT * result = search(0x100000000 - *target, start);
				printComment(*target);
				setZero();
				printf("\t\tsub eax, %xH\n\t\tsub eax, %xH\n\t\tsub eax, %xH\n", result->result_a, result->result_b, result->result_c);
				printf("\t\tpush eax\n");
				free(result);
				target--;
		}
		printNOP(32);
}


void showHelp(char *filename){
		printf("Usage : \n");
		printf("\t%s [SHELLCODE_FILE_NAME]\n", filename);
		printf("Examples : \n");
		printf("\t [Step1] : %s shellcode\n", filename);
		printf("\t [Step2] : (Copy the output asm code to a file, I use ./printable_shellcode.asm)\n");
		printf("\t [Step3] : make printable_shellcode\n");
		printf("\t [Step4] : objdump -d printable_shellcode\n");
		printf("\t [Step5] : (Copy the binary code to a file, I use ./printable_shellcode.dat)\n");
		printf("\t [Step6] : cat ./printable_shellcode.dat\n");
		printf("\t [Step7] : (Copy file content)\n");
		printf("\t [Step8] : (Use a text editor to add '\\x')\n");
		printf("\t [Step9] : (Open python)\n");
		printf("\t [Step10] : >>> with open(\"result\", \"w\") as f:\n");
		printf("\t [Step11] : >>> \tf.write(\"[The  text you have just copied]\")\n");
		printf("\t [Step12] : python ./exploit.py ./result\n");
		printf("Note : \n");
		printf("\tIf you have any questions, please send an email to me.(wangyihanger@gmail.com)\n");
		printf("\tMy honor to help you with your problem.\n");
		printf("Author : \n");
		printf("\tWangYihang\n");
		printf("Date : \n");
		printf("\t2017/03/21\n");
}

