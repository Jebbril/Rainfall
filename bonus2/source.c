#include <stdlib.h>
#include <string.h>

int language;

void greetuser(char *buf) {
    char    greeting[72];
    char    *greet;

    if (language == 1)
        greet = "Hyvää päivää ";
    else if (language == 2)
        greet = "Goedemiddag! ";
    else
        greet = "Hello ";
    
    strcpy(greeting, greet);
    strcat(greeting, buf);

    puts(greeting);
}

int main(int ac, char **av) {
    char    buf[76];

    if (ac != 3)
        return 1;

    memset(buf, 0, sizeof(buf));

    strncpy(buf, av[1], 40);
    strncpy(buf + 40, av[2], 32);

    char    *lang = getenv("LANG");
    if (lang) {
        if (memcmp(lang, "fi", 2) == 0)
            language = 1;
        if (memcmp(lang, "nl", 2) == 0)
            language = 2;
    }

    greetuser(buf);

    return 0;
}