#include <cstdlib>
#include <iostream>
#include "gauss.h"

using namespace std;

int main(int argc, char *argv[])
{
    for (int i=1;i<argc;i++)
    {
        Gauss gauss =  Gauss(argv[1]);
        double * res = gauss.solve();
        printf ("RUNNING ON TEST: %s\n",argv[i]);
        for (int i=0;i<gauss.getSize();i++)
        {
            printf ("%8.3lf  ",res[i]);
        }
        printf ("\n");
        delete res;
    }
    return 0;

}
