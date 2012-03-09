#include <iostream>
#include "gauss.h"
using namespace std;



int main(int argc, char *argv[])
{
    for (int i=1;i<argc;i++)
    {
        printf ("RUNNING ON TEST: %s\n",argv[i]);
        Gauss gauss =  Gauss(argv[i]);
        double ** res = NULL;
        try
        {
            res = gauss.invert();
        }
        catch (DivByZeroException e)
        {
            printf ("ERR::DIVIZION BY ZERO\n");
            continue;
        }
        double det = gauss.det();
        printf ("det (A) = %8.3lf\n",det);
        printf("det(A)*A^-1:\n");
        for (int i=0;i<gauss.getSize();i++)
        {
            for (int j=0;j<gauss.getSize();j++) printf ("%8.2lf",det*res[i][j]);
            printf ("\n");
        }
        for (int i=0;i<gauss.getSize();i++) delete [] res[i];
        delete [] res;
    }
    return 0;

}

