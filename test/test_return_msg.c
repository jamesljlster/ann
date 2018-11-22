#include <ann.h>
#include <stdio.h>

int main()
{
    int i;

    for (i = 2; i > -8; i--)
    {
        printf("With return value: %d, error message is: %s.\n", i,
               ann_get_error_msg(i));
    }

    return 0;
}
