#include <cstdlib>
#include <iostream>
#include "gauss.h"

using namespace std;

int main(int argc, char *argv[])
{
    Gauss gauss =  Gauss("test.in");
    double * res = gauss.solve();
    for (int i=0;i<gauss.getSize();i++)
    {
        printf ("%8.3lf  ",res[i]);
    }
    printf ("\n");
    delete res;
    return 0;
}
