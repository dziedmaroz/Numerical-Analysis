#include "krylov.h"
#include "gauss/gauss.h"

Krylov::Krylov(char *filename)
{
    FILE* fin = fopen(filename,"r");
    fscanf (fin,"%d\n",&size);
    matrix = new double* [size];
    for (int i=0;i<size;i++)
    {
        matrix[i]= new double [size];
        for (int j=0;j<size;j++)
        {
            fscanf(fin,"%lf",&matrix[i][j]);
        }
    }
    c_0 = new double [size];
    for (int i=0;i<size;i++)
    {
        fscanf (fin,"%lf",&c_0[i]);
    }
    fclose (fin);
}

double* Krylov::mulMatrix(double* x)
    {
        double* res = new double[size];
        for (int i = 0; i < size; i++)
        {
            res[i] = 0;
            for (int j = 0; j <size; j++) {res[i] += x[j] * matrix[i][j];}
        }
        return res;
    }

Krylov::~Krylov ()
{
    for (int i=0;i<size;i++) delete [] matrix[i];
    delete [] matrix;
    delete [] c_0;
}

double* Krylov::getPoly ()
{
    double** Q = new double* [size];
    for (int i=0;i<size;i++)
    {
        Q[i] = new double[size+1];
    }
    double* c = new double [size];
    for (int i=0;i<size;i++)
    {
        c[i]= c_0[i];
    }
    for (int i=0;i<size+1;i++)
    {
        for (int j=0;j<size;j++)
        {
            Q[j][((size+1)+size-1-i)%(size+1)] = c[j];
        }
        c = mulMatrix (c);

    }
    Gauss gauss = Gauss(Q,size);
    int m = 0;
    double* p = gauss.solve (m);
    if (m==size)
    {
        return p;
    }
    else
    {
        printf ("Only %d steps on get Poly\n",m);
    }
    for (int i=0;i<size;i++) delete [] Q[i];
    delete [] Q;
    delete [] c;
    return NULL;
}

double* Krylov::getEigenVector (double* poly, double eigenVal)
{
    double* vector = new double [size];
    vector[0]=1;
    for (int i=1;i<size;i++)
    {
        vector[i] = vector[i-1]*eigenVal-poly[i-1];
    }
    return vector;
}

