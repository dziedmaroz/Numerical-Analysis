#ifndef GAUSS_H
#define GAUSS_H

#include <cstdlib>
#include <stdio.h>
#include <math.h>

using namespace std;


class Gauss
{
private:
    double** matrix;
    unsigned int size;
    double** copy (const double** source);
    double** getIndent ();
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
    Gauss (char* filename);
    int getSize() {return size;}
    double det ();
    ~Gauss();
};

#endif // GAUSS_H
