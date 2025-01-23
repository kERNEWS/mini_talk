#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"
void handle_signal(int signal, siginfo_t *info, void *cotext)
{
    static unsigned int bit_count;
    static char c;
    int client_pid;

    if (SIGUSR2 == signal)
        c |= 1;  
    bit_count++;
    client_pid = info->si_pid;
    if (bit_count == 8)
    {
        if (c == '\0')
        {
            printf("\n");
            kill(client_pid, SIGUSR1);
        }
        else
        {
            write(1, &c, 1);
            kill(client_pid, SIGUSR1);
        }
        bit_count = 0;
        c = 0;
    }
    else
        c = c << 1;
}
int main(void)
{

    struct sigaction action;

    __pid_t PID;
    PID = getpid();
    printf("%i\n", PID);
    action.sa_sigaction = handle_signal;
    action.sa_flags = SA_SIGINFO;
    sigemptyset(&action.sa_mask);
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);
    while (1)
        pause();
    return(0);
    
}