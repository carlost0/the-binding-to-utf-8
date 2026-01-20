#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    time_t time_now = time(NULL);
    for (;;) {
        printf("%ld\n", time(NULL));
        sleep(1);
    }
    return 0;
}
