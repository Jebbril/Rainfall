#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int n() {
    return system("/bin/cat /home/user/level7/.pass");
}

int m() {
    return puts("Nope");
}

int main(int ac, char **av) {
    char    *buff = malloc(64);
    int     (**f_ptr)() = malloc(4);

    *f_ptr = m;
    strcpy(buff, av[1]);
    
    return (*f_ptr)();
}