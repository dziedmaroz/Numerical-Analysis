#include "gauss.h"

Gauss::Gauss (char *filename)
{
    FILE* fin = fopen (filename,"r");
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
    permutation = new int [size];
    for (int i=0;i<size;i++)
    {
        permutation [i]= i;
    }
    fclose (fin);
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


void  Gauss::copy (  double** source, double** &dest)
{
    double** tmp = new double* [this->size];
    for (int i=0;i<this->size;i++)
    {
        tmp[i]=new double [size];
        for (int j=0;j<this->size;j++)
        {
            tmp[i][j]=source[i][j];
        }
    }
    dest = tmp;
}

double** Gauss::getIndent(int sz)
{
    double** tmp = new double* [sz];
    for (int i=0;i<sz;i++)
    {
        tmp[i]=new double [sz];
        for (int j=0;j<sz;j++)
        {
            if (i==j)
            {
                tmp[i][j]=1;
            }
            else
            {
                tmp[i][j]=0;
            }
        }
    }
    return tmp;
}

double Gauss::det()
{

    double** matrCopy = NULL;
    copy(this->matrix,matrCopy);    
    double d = 1;

    for (int i=0;i<size;i++)
    {

        Position dominantPos = findDominant(i,matrCopy);
        double dominant = matrCopy[dominantPos.m][dominantPos.n];
        if (fabs(dominant)<pow(10,-20)) throw DivByZeroException ();
        if (dominantPos.m==i)
        {
            swapColumns(i,dominantPos.n,matrCopy);
        }
        if (dominantPos.n==i)
        {
            swapRows(i,dominantPos.m, matrCopy);
        }
        d *= dominant;
        for (int j=i;j<size;j++)
        {
            matrCopy[i][j]/=dominant;
        }

        for (int j=i+1;j<size;j++)
        {
            double first = matrCopy[j][i];
            for (int k=i;k<size;k++)
            {
                matrCopy[j][k]=matrCopy[j][k] - first*matrCopy[i][k];
            }
        }
    }

    for (int i=0;i<size;i++)
    {
        delete[] matrCopy[i];
    }
    delete[] matrCopy;
    return d;
}
Gauss::Position Gauss::findDominant(int k, double **&matr)
{
    Position pos;
    pos.m = k;
    pos.n = k;
    for (int i=k;k<size;k++)
    {
        if (fabs(matr[i][k])>fabs(matr[pos.m][pos.n]))
        {
            pos.m = i;
            pos.n = k;
        }
        if (fabs(matr[k][i])>fabs(matr[pos.m][pos.n]))
        {
            pos.m = k;
            pos.n = i;
        }
    }
    return pos;
}

void Gauss::swapRows(int x, int y, double **&matr)
{
    for (int i=0;i<size;i++)
    {
        double tmp = matr[x][i];
        matr [x][i] = matr[y][i];
        matr [y][i] = tmp;
    }
}

void Gauss::swapColumns(int x, int y, double **&matr)
{
    for (int i=0;i<size;i++)
    {
        double tmp = matr[i][x];
        matr [i][x] = matr[i][y];
        matr [i][y] = tmp;
    }
    int tmp = permutation[x];
    permutation [x] = permutation[y];
    permutation [y] = tmp;
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

double** Gauss::invert()
{
    double** matrCopy = NULL;
    copy(this->matrix,matrCopy);
    double** indent = getIndent(this->size);
    for (int i=0;i<size;i++)
    {
        printMatrix(matrCopy, size);
        printf("   ---\n");
        printMatrix(indent,size);
        printf("\n\n");
        Position dominantPos = findDominant(i,matrCopy);
        double dominant = matrCopy[dominantPos.m][dominantPos.n];
        if (fabs(dominant)<pow(10,-20)) throw DivByZeroException ();
        if (dominantPos.m==i)
        {
            swapColumns(i,dominantPos.n,matrCopy);
            swapColumns(i,dominantPos.n,indent);
        }
        if (dominantPos.n==i)
        {
            swapRows(i,dominantPos.m, matrCopy);
            swapRows(i,dominantPos.m, indent);
        }
        for (int j=i;j<size;j++)
        {
            matrCopy[i][j]/=dominant;
            indent[i][j]/=dominant;
        }

        for (int j=i+1;j<size;j++)
        {
            double first = matrCopy[j][i];
            for (int k=i;k<size;k++)
            {
                matrCopy[j][k]=matrCopy[j][k] - first*matrCopy[i][k];
            }
        }
    }
    for (int i=size-1;i>=0;i--)
    {
        for (int j=i-1;j>=0;j--)
        {
            double tmp = matrCopy[j][i];
            for (int k=0;k<size;k++)
            {
                matrCopy[j][k]-=matrCopy[i][k]*tmp;
                indent[j][k]-=indent[i][k]*tmp;
            }
        }
    }

    printMatrix(matrCopy, size);
    printf("   ---\n");
    printMatrix(indent,size);
    printf("\n\n");
    for (int i=0;i<size;i++)
    {
        delete[] matrCopy[i];
        delete[] indent[i];
    }
    delete[] matrCopy;
    delete [] indent;
    return NULL;

}

void Gauss::printMatrix (double ** matrix, int size)
{
    for (int i=0;i<size;i++)
    {
        for (int j=0;j<size;j++)
        {
            printf("%8.3lf ",matrix[i][j]);
        }
        printf ("\n");
    }
}
