#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int a = 5, b = 6, i = 0;
    char str1[7] = "pickle";
    char str2[7] = "banana";

    printf ("Before a = %d, b = %d\n", a, b);

    swap (&a, &b);

    printf ("\nAfter a = %d, b = %d\n", a, b);

    printf ("\n\nstr1 Before\n");

    while (str1[i])
    {
        printf ("%c", str1[i]);

        i++;
    }

    i = 0;

    printf ("\n\nstr2 Before\n");

    while (str2[i])
    {
        printf ("%c", str2[i]);

        i++;
    }

    i = 0;



    scpy(&str1, &str2);



    printf ("\n\nstr1 After\n");

    while (str1[i])
    {
        printf ("%c", str1[i]);

        i++;
    }

    i = 0;

    printf ("\n\nstr2 After\n");

    while (str2[i])
    {
        printf ("%c", str2[i]);

        i++;
    }

    printf ("\n");

    return 0;
}



int swap (int *a, int *b)
{
    int t;

    t = *a;
    *a = *b;
    *b = t;
}

void scpy (char *a, char *b)
{
    while (*a++ = *b++);
}
