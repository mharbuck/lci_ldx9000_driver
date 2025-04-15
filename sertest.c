// C library headers
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()


const int a = 1;
const int b = a +1;

typedef struct foo_t {
    int a, b, c;
} foo_t;

const foo_t foo_init = { 1, 2, 3 };
foo_t my_foo = foo_init;

int main()
{
    return 0;
}




