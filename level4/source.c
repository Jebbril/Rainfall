#include <stdio.h>

int m;

int p(char *buff) {
    return printf(buff);
}

int n() {
    char    buff[520];

    fgets(buff, 512, stdin);
    p(buff);

    if (m != 0x1025544)
        return m;

    return system("/bin/cat /home/user/level5/.pass");
}

int main(void) {
    return n();
}