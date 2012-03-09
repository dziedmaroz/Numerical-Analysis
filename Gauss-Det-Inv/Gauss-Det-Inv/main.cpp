#include <iostream>
#include "gauss.h"
using namespace std;


int main ()
{
    Gauss matr =  Gauss ("input.in");
    cout<<matr.det()<<endl;
    matr.invert();
}
