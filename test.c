#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    int a = 0;
    int b = 0;

    a++;
    ++b;

    printf("a: %d\nb: %d", a, b);
    return 0;
}

