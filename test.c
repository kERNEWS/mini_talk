#include <unistd.h>
#include <stdio.h>


int main()
{
    char c = 'a';
    char temp = c;
    int i = 1;
	temp = (c >> i) & 1;
    printf("%i", temp);
}