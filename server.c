#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

void handle_signal(int signal)
{

    static unsigned int bit_count;
    static char c;

    c |= (signal == SIGUSR2);
    bit_count++;
    if (bit_count == 8)
    {
        if (c == '\0')
            printf("\n");
        else
        {
            printf("%c", c);
        }
        bit_count = 0;
        c = 0;
    }
    else
        c = c << 1;

}

int main(void)
{
    __pid_t PID;
    PID = getpid();
    printf("%i\n", PID);
    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);
    while (1)
        pause();
    return(0);
    
}