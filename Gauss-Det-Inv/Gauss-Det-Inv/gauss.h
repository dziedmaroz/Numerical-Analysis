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
    int *permutationColumns;
    int *permutationRows;

    struct Position
    {
        unsigned int n;
        unsigned int m;
    };

    void permutate (double* &x);
    Position findDominant (uint k, double** &matr);
    void swapRows (int x, int y, double** &matr, bool chVector);
    void swapColumns (int x, int y, double** &matr, bool chVector);
public:
    Gauss (char* filename);
    int getSize() {return size;}
    double det ();
    double** invert ();
    void printMatrix (double ** matrix, int size);
    ~Gauss();
};

#endif // GAUSS_H
