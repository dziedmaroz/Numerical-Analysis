#include <iostream>
#include <square.h>

int main(int argc, char *argv[])
{
    for (int i=1;i<argc;i++)
    {
        Square sq =  Square(argv[i]);
        double* res;
        try
        {
            res  = sq.solve();
            for (int i=0;i<sq.getSize();i++)
            {
                printf ("%3.3lf  ",res[i]);
            }
            printf ("\n");
            delete [] res;
        }
        catch (DivByZeroException e)
        {
            printf ("DivByZero\n");
        }
    }
    return 0;
}
