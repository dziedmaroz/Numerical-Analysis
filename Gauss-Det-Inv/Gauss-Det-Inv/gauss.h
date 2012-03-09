#ifndef GAUSS_H
#define GAUSS_H

#include <cstdlib>
#include <stdio.h>
#include <math.h>

using namespace std;

struct DivByZeroException {};
class Gauss
{
private:
    double** matrix;
    unsigned int size;
    void copy (  double** source, double** &dest);
    double** getIndent (int sz);
    int *permutation;

    struct Position
    {
        unsigned int n;
        unsigned int m;
    };

    void permutate (double* &x);
    Position findDominant (int k, double** &matr);
    void swapRows (int x, int y, double** &matr);
    void swapColumns (int x, int y, double** &matr);
public:
    Gauss (char* filename);
    int getSize() {return size;}
    double det ();
    double** invert ();
    void printMatrix (double ** matrix, int size);
    ~Gauss();
};

#endif // GAUSS_H
