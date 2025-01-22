#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"
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

int main (int argc, char *argv[])
{
    char *message;
    __pid_t PID;



    if (argc != 3)
    {
        printf("Usage:./client <PID> <Message>\n");
        return (1);
    }
    message = argv[2];
    PID = ft_atoi(argv[1]);
    printf("%s\n", message);
    printf("%i\n", PID);

}