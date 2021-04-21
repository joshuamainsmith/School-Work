#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int choice = 1;

    while (choice)
    {
        int a = 0, b = 0;

        printf ("Enter an integer: ");
        scanf ("%d", &a);

        printf ("Enter an integer: ");
        scanf ("%d", &b);

        printf ("Enter 0 for addition, 1 for subtraction: ");
        scanf ("%d", &choice);

        if (choice == 0)
        {
            a = a + b;
        }

        else
        {
            a = a - b;
        }

        printf ("The result is %d\n", a);

        printf ("Enter zero to quit and anything else to continue ");
        scanf("%d", &choice);
    }

    return 0;
}
