#include <stdio.h>
#include <string.h>
#include <unistd.h>

void    p(char *dest, char *prompt) {
    char    buff[4014];

    puts(prompt);
    read(0, buff, 4096);

    char    *newline = strchr(buff, '\n');
    if (newline)
        *newline = 0;
    
    strncpy(dest, buff, 20);
}

void    pp(char *buff) {
    char    half1[20];
    char    half2[20];

    p(half1, " - ");
    p(half2, " - ");
    strcpy(buff, half1);

    size_t  len = strlen(buff);
    buff[len] = " ";
    buff[len] = 0;

    strcat(buff, half2);
}

int main(void) {
    char    buff[50];

    pp(buff);
    puts(buff);
    
    return 0;
}