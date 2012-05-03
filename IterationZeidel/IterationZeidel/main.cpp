#include <cstdlib>
#include <iostream>
#include "iterationzeidel.h"

using namespace std;

int main(int argc, char *argv[])
{
    for (int i=1;i<argc;i++)
    {
        printf ("RUNNING ON TEST: %s\n",argv[i]);
        IterationZeidel iter =  IterationZeidel(argv[i]);
        double * res = NULL;
        try
        {
            iter.makeIterable();
        }
        catch (DivByZeroException e)
        {
            printf ("ERR::DIVIZION BY ZERO\n");
            continue;
        }
        iter.solveIteration();
        iter.solveZeidel();
        printf ("\n");
        delete res;
    }
    return 0;

}

