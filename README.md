####Description : 
```
	This is a sample tool which can make your shellcode printable.
```
####Usage : 
```
	./Creator [SHELLCODE_FILE_NAME]
```
####Examples : 
```
	 [Step1] : ./Creator shellcode
	 [Step2] : (Copy the output asm code to a file, I use ./printable_shellcode.asm)
	 [Step3] : make printable_shellcode
	 [Step4] : objdump -d printable_shellcode
	 [Step5] : (Copy the binary code to a file, I use ./printable_shellcode.dat)
	 [Step6] : cat ./printable_shellcode.dat
	 [Step7] : (Copy file content)
	 [Step8] : (Use a text editor to add '\x')
	 [Step9] : (Open python)
	 [Step10] : >>> with open("result", "w") as f:
	 [Step11] : >>> 	f.write("[The  text you have just copied]")
	 [Step12] : python ./exploit.py ./result
```
####Note : 
```
	If you have any questions, please send an email to me.(wangyihanger@gmail.com)
	My honor to help you with your problem.
```
####TODO : 
```
	1. Use more register to build the shellcode
	2. Use less subtraction to set the register
```
####Author : 
```
	WangYihang(wangyihanger@gmail.com)
```
####Date : 
```
	2017/03/21
```
