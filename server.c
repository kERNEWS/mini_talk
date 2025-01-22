#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

int main(void)
{
    __pid_t PID;
    PID = getpid();
    printf("%i\n", PID);
}