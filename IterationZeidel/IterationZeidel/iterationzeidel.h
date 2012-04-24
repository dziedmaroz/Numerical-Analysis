#ifndef ITERATIONZEIDEL_H
#define ITERATIONZEIDEL_H

#include <stdio.h>
#include <cmath>

struct DivByZeroException{};

class IterationZeidel
{

    double** matrix;    
    int size;
    double* x0;
    double epsilon;
    int* permutation;
    struct Position
    {
        unsigned int n;
        unsigned int m;
    };
    void permutate (double* &x);
    Position findDominant (int k);
    void swapRows (int x, int y);
    void swapColumns (int x, int y);
    double normMatrix (double** matr, int sz);
    double normVector (double* vector, int sz);


public:
    IterationZeidel(char* filename);
    double* solveIteration();
    void makeIterable ();
    ~IterationZeidel();
};

#endif // ITERATIONZEIDEL_H
