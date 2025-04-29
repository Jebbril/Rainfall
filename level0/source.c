#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int ac, char **av) {
    if (atoi(av[1]) != 423)
        fwrite("No !\n", 1, 5, stderr);
    else {
        char    *buff = strudup("/bin/sh");
        int     unused = 0;
        int     gid = getegid();
        int     uid = geteuid();
        
        setresgid(gid, gid, gid);
        setresuid(uid, uid, uid);
        execv("/bin/sh", &buff);
    }

    return 0;
}