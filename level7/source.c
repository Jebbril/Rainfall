#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

char    c[68];

struct node {
    int     num;
    char    *str;
};

int m() {
    return printf("%s - %d\n", c, time(0));
}

int main(int ac, char **av) {
    struct node *node1;
    struct node *node2;
    FILE        *file;

    node1 = (struct node *)malloc(8);
    node1->num = 1;
    node1->str = (char *)malloc(8);

    node2 = (struct node *)malloc(8);
    node2->num = 2;
    node2->str = (char *)malloc(8);

    strcpy(node1->str, av[1]);
    strcpy(node2->str, av[2]);

    file = fopen("/home/user/level8/.pass", "r");
    fgets(c, 68, file);
    
    puts("~~");

    return 0;
}
