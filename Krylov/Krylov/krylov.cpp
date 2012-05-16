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
        double[] res = new double[size];
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
        Q[i][0]=c[i];
    }
    for (int i=0;i<size;i++)
    {
        double* tmp = new double [size];
        tmp = mulMatrix (c);
        for (int j=0;j<size;j++)
        {
            c[j]=tmp[j];
            Q[j][i+1] = c[j];
        }
        delete [] tmp;
    }

    Gauss gauss = Gauss(Q,size);
    int m = 0;
    double* p = gauss.solve (m);
    if (m==size)
    {
        for (int i=0;i<size;i++) printf ("%3.3lf ",p[i]);
    }
    for (int i=0;i<size;i++) delete [] Q[i];
    delete [] Q;
    delete [] c;
}
