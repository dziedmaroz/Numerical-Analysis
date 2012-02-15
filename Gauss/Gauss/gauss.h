#ifndef GAUSS_H
#define GAUSS_H

#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

struct DivByZeroException {};
struct CannotSolve {};
class Gauss
{
    double ** matrix;
    unsigned int size;
    int *permutation;

    struct Position
    {
        unsigned int n;
        unsigned int m;
    };

    void permutate (double* &x);
    Position findDominant (int k);
    void swapRows (int x, int y);
    void swapColumns (int x, int y);
public:
    Gauss(char* filename);
    double* solve ();
    int getSize() {return size;}
    ~Gauss ();
};

#endif // GAUSS_H
