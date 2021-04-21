#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[4]={5, 6, 7, 8};
    int i = 0;
    int copy0=0, copy1=0;

    for (i=0; i <= 3; i++)
    {
        if ((a[i] % 2) == 0)
        {
            copy0 += a[i];
        }
        else
        {
            copy1 += a[i];
        }
    }

    printf ("C0 = %d, C1 = %d\n", copy0, copy1);

    return 0;
}
