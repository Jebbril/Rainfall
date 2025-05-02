#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

char    *p() {
    char    buff[76];

    gets(buff);
    uintptr_t   ret_addr = __builtin_return_address(0);
    if ((ret_addr & 0xb0000000) != 0xb0000000) {
        puts(buff);
        return strdup(buff);
    }

    printf("(%p)\n", ret_addr);
    exit(1);
}

int main(void) {
    return p();
}