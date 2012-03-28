#include <iostream>
#include <square.h>

int main(int argc, char *argv[])
{
    Square sq =  Square("input.txt");
    double* res  = sq.solve();
    for (int i=0;i<sq.getSize();i++)
    {
        printf ("%3.3lf  ",res[i]);
    }
    printf ("\n");

    return 0;
}
