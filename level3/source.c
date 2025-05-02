#include <stdio.h>

int m;

int v() {
    char    buff[520];

    fgets(buff, 512, stdin);
    printf(buff);

    if (m != 64)
        return m;
    
    fwrite("Wait what?!\n", 1, 12, stdout);
    return system("/bin/sh");
}

int main(void) {
    return v();
}