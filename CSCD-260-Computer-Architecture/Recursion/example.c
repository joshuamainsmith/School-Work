#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int x = 0, y = 0;

    printf ("Enter an integer: ");
    scanf ("%d", &x);

    printf ("\nRecursive add of %d is: %d", x, rec(x));


    return 0;
}

int rec (n)
{
    if (n == 0)
        return 0;
    return (n + rec(n - 1));
}
