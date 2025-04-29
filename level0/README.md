this is as easy as it gets, we can see in the disassembly of the binary in `source.asm` :
```x86asm
0x08048ec9 <+9>:	mov    eax,DWORD PTR [ebp+0xc]
0x08048ecc <+12>:	add    eax,0x4
0x08048ecf <+15>:	mov    eax,DWORD PTR [eax]
0x08048ed1 <+17>:	mov    DWORD PTR [esp],eax
0x08048ed4 <+20>:	call   0x8049710 <atoi> ; calling atoi to convert av[1] to an int
0x08048ed9 <+25>:	cmp    eax,0x1a7 ; comparing the result to 0x1a7(423)
0x08048ede <+30>:	jne    0x8048f58 <main+152> ; a jump depending on the comparison
```

if you enter the number `423` as a first argument you continue execution to the execv call :
```x86asm
0x08048f51 <+145>:	call   0x8054640 <execv> ; execv("/bin/sh", &buffer)
```

else it will jump to the fwrite call :
```x86asm
0x08048f7b <+187>:	call   0x804a230 <fwrite> ; fwrite("No !\n", 1, 5, stderr)
```

```bash
level0@RainFall:~$ ./level0 423
$ pwd                         
/home/user/level0
$ cat /home/user/level0/.pass
cat: /home/user/level0/.pass: Permission denied
$ cat /home/user/level1/.pass    
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
$ 
```

and there you go.