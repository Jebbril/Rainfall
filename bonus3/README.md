this challenge is as easy as it gets.

it reads from a file containing the password and put the result in a local buffer, then it compares the first part with our first arg passed after null terminating that first part in index that we get with `atoi` of our passed arg.

```c
fread(buf, 1, 66, fd);

value = atoi(av[1]);
buf[value] = 0;
```

if we give our program an empty string then `atoi` will convert it to 0.
we put 0 in index 0 of our buffer. and then when we compare them using `strcmp` it will return 0 passing the test

```c
fread(buf, 1, 66, fd);

value = atoi(""); => equals 0
buf[0] = 0;
...
strcmp(buf, av[1]) == 0 => will give us true
```

```bash
bonus3@RainFall:~$ ./bonus3 ""
$ pwd
/home/user/bonus3
$ cat /home/user/end/.pass
3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
```

and there you go.