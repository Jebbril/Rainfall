#include <stdio.h>
#include <stdlib.h>

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