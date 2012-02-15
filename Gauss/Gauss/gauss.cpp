#include "gauss.h"

struct DivByZeroException {};
struct CannotSolve {};
Gauss::Gauss (char *filename)
{
    FILE* fin = fopen (filename,"r");
    fscanf (fin,"%d\n",&size);
    matrix = new double* [size];
    for (int i=0;i<size;i++)
    {
        matrix[i]= new double [size+1];
        for (int j=0;j<size;j++)
        {
            fscanf(fin,"%lf",&matrix[i][j]);
        }
        fscanf (fin,"%lf\n",&matrix[i][size]);
    }
    permutation = new int [size];
    for (int i=0;i<size;i++)
    {
        permutation [i]= i;
    }
    fclose (fin);
}


Gauss::Position Gauss::findDominant(int k)
{
    Position pos;
    pos.m = k;
    pos.n = k;
    for (int i=k;k<size;k++)
    {
        if (fabs(matrix[i][k])>fabs(matrix[pos.m][pos.n]))
        {
            pos.m = i;
            pos.n = k;
        }
        if (fabs(matrix[k][i])>fabs(matrix[pos.m][pos.n]))
        {
            pos.m = k;
            pos.n = i;
        }
    }
    return pos;
}

void Gauss::swapRows(int x, int y)
{
    for (int i=1;i<size+1;i++)
    {
        double tmp = matrix[x][i];
        matrix [x][i] = matrix[y][i];
        matrix [y][i] = tmp;
    }
}

void Gauss::swapColumns(int x, int y)
{
    for (int i=0;i<size;i++)
    {
        double tmp = matrix[i][x];
        matrix [i][x] = matrix[i][y];
        matrix [i][y] = tmp;
    }
    int tmp = permutation[x];
    permutation [x] = permutation[y];
    permutation [y] = tmp;
}

double* Gauss::solve()
{
    for (int i=0;i<size;i++)
    {
        Position dominantPos = findDominant(i);
        double dominant = matrix[dominantPos.m][dominantPos.n];
        if (fabs(dominant)<pow(10,-20)) throw DivByZeroException ();
        if (dominantPos.m==i)
        {
            swapColumns(i,dominantPos.n);
        }
        if (dominantPos.n==i)
        {
            swapRows(i,dominantPos.m);
        }

        for (int j=i;j<size+1;j++)
        {
            matrix[i][j]/=dominant;
        }

        for (int j=i+1;j<size;j++)
        {
            double first = matrix[j][i];
            for (int k=i;k<size+1;k++)
            {
                matrix[j][k]=matrix[j][k] - first*matrix[i][k];
            }
        }
    }

    double* X = new double [size];
    for (int i=size-1;i>-1;i--)
    {
        double x = matrix[i][size];
        for (int j=i+1;j<size;j++)
        {
            x -= matrix[i][j]*X[j];
        }
        if (matrix[i][i]==0)
        {
            throw CannotSolve();
        }
        X[i]=x/matrix[i][i];
    }
    permutate (X);

    return X;
}

void Gauss::permutate(double *&x)
{
    double* res = new double [size];
    for (int i=0;i<size;i++)
    {
        res[permutation[i]]=x[i];
    }
    for (int i=0;i<size;i++)
    {
        x[i]=res[i];
    }
    delete res;
}

Gauss::~Gauss()
{
    for (int i=0;i<size;i++)
    {
        delete matrix[i];
    }
    delete matrix;
    delete permutation;
}
