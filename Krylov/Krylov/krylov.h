#ifndef KRYLOV_H
#define KRYLOV_H

#include <cstdio>

class Krylov
{
    double** matrix;
    double* c_0;
    int size;
    double* mulMatrix (double* y);
public:
    Krylov(char* filename);
    double* getPoly ();
    int getSize (){return size;}
    ~Krylov();
    double* getEigenVector(double*, double);
};

#endif // KRYLOV_H
