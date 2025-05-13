#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **av) {
    char    buf[40];
    int     value;

    value = atoi(av[1]);
    if (value <= 9) {
        memcpy(buf, av[2], value * 4);
        if (value == 0x574f4c46)
            execl("/bin/sh", "sh", 0);
        return 0;
    }
    
    return 1;
}