#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"
struct sigaction	s_sigaction;
void handle_signal(int signal)
{

    static unsigned int bit_count;
    static char c;

    if (bit_count < 8)
        c = c << 1;
    if (SIGUSR2 == signal)
        c |= 1;
        
    bit_count++;
    printf("sig received\n");
    if (bit_count == 8)
    {
        if (c == '\0')
            printf("\n");
        else
        {
            write(1, &c, 1);
            write(1, "\n", 1);
        }
        bit_count = 0;
        c = 0;
    }
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