#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char    *auth = NULL;
char    *service = NULL;

int main(void) {
    char    buff[128];

    while (1) {
        printf("%p, %p \n", auth, service);

        if (fgets(buff, 128, stdin) == NULL)
            return 0;
        
        if (strncmp(buff, "auth ", 5) == 0) {
            auth = (char *)malloc(4);
            *auth = 0;
            char    *auth_data = buff + 5;
            if (strlen(auth_data) < 30)
                strcpy((char *)auth, auth_data);
        }
        else if (strncmp(buff, "reset", 5) == 0) {
            free(auth);
            auth = NULL;
        }
        else if (strncmp(buff, "service", 7) == 0) {
            free(service);
            service = strdup(buff + 7);
        }
        else if (strncmp(buff, "login", 5) == 0) {
            if (auth != NULL && auth[8] != 0)
                system("/bin/sh");
            else
                fwrite("Password:\n", 1, 10, stdout);
        }
    }

    return 0;
}