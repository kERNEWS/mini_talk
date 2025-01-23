#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

volatile int ack_received;

static int	is_space(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
	{
		return (1);
	}
	return (0);
}

static int	check_sign(char c)
{
	if (c == '-')
	{
		return (-1);
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		res;
	int		sign;

	i = 0;
	res = 0;
	while (is_space(nptr[i]))
	{
		i++;
	}
	sign = check_sign(nptr[i]);
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	res *= sign;
	return (res);
}

void wait_for_server(int signum)
{
	(void)signum;
	ack_received = 1;
}

void send_message(char c, int pid)
{
	int i;
	unsigned char temp;

	i = 8;
	while (i > 0)
	{
		i--;
		temp = (c >> i) & 1;
		if (temp == 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		ack_received = 0;
		while(ack_received == 0)
			pause();
	}
}

int main (int argc, char *argv[])
{
	struct sigaction ack;
    char *message;
    __pid_t PID;
	int i;

	i = 0;
    if (argc != 3)
    {
        printf("Usage:./client <PID> <Message>\n");
        return (1);
    }
    message = argv[2];
    PID = ft_atoi(argv[1]);
    printf("%s\n", message);
    printf("%i\n", PID);

	ack.sa_handler = wait_for_server;
	sigemptyset(&ack.sa_mask);
	ack.sa_flags = 0;
	sigaction(SIGUSR1, &ack, NULL);


	while(message[i])
	{
		send_message(message[i], PID);
		i++;
	}
	send_message('\0', PID);
}