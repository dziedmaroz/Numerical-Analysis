#ifndef KRYLOV_H
#define KRYLOV_H

#include <stdio>

class Krylov
{
    double** matrix;
    double* c_0;
    double size;
    double* mulMatrix (double* y);
public:
    Krylov(char* filename);
    double* getPoly ();
};

#endif // KRYLOV_H
