#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **av) {
    FILE    *fd;
    char    buf[128] = {0};
    int     value;

    fd = fopen("/home/user/end/.pass", 'r');
    if (!fd || ac != 2)
        return -1;
    
    fread(buf, 1, 66, fd);

    value = atoi(av[1]);
    buf[value] = 0;

    fread(buf + 66, 1, 65, fd);
    fclose(fd);

    if (strcmp(buf, av[1]) == 0)
        execl("/bin/sh", "sh", NULL);
    else
        puts(buf + 66);

    return 0;
}