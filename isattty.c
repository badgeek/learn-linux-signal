#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int x = isatty(fileno(stdout));

    fprintf(stderr, "test aja\n");

    printf("tty: %i", x);
}