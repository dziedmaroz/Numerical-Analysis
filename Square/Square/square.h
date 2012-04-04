#include <cmath>
#include <stdio.h>

struct DivByZeroException {};

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
