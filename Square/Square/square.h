#ifndef SQUARE_H
#define SQUARE_H

#include <cmath>
#include <stdio.h>

class Square
{
    double** matrix_;
    int sz;
    double* f;
    double sgn (double x);
public:
    Square(char *filename);
    double* solve ();
    int getSize () {return sz;}
    ~Square ();
};

#endif // SQUARE_H
