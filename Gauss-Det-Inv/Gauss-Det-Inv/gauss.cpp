#include "gauss.h"

Gauss::Gauss (char *filename)
{
    FILE* fin = fopen (filename,"r");
    fscanf (fin,"%d\n",&size);
    matrix = new double* [size];
    for (uint i=0;i<size;i++)
    {
        matrix[i]= new double [size];
        for (uint j=0;j<size;j++)
        {
            fscanf(fin,"%lf",&matrix[i][j]);
        }
    }
    permutationColumns = new int [size];
    permutationRows = new int [size];
    for (uint i=0;i<size;i++)
    {
        permutationColumns [i]= i;
        permutationRows[i]=i;
    }
    fclose (fin);
}

Gauss::~Gauss()
{
    for (uint i=0;i<size;i++)
    {
        delete matrix[i];
    }
    delete matrix;
    delete permutationColumns;
}


void  Gauss::copy (  double** source, double** &dest)
{
    double** tmp = new double* [this->size];
    for (uint i=0;i<this->size;i++)
    {
        tmp[i]=new double [size];
        for (uint j=0;j<this->size;j++)
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
    double sgn = 1;

    for (uint i=0;i<size;i++)
    {

        Position dominantPos = findDominant(i,matrCopy);
        double dominant = matrCopy[dominantPos.m][dominantPos.n];
        if (fabs(dominant)<pow(10,-20)) throw DivByZeroException ();
        if (dominantPos.m==i && dominantPos.n!=i)
        {
            swapColumns(i,dominantPos.n,matrCopy, true);
            sgn*=-1;
        }
        if (dominantPos.n==i && dominantPos.m!=i)
        {
            swapRows(i,dominantPos.m, matrCopy, true);
            sgn*=-1;
        }
        d *= dominant;
        for (uint j=i;j<size;j++)
        {
            matrCopy[i][j]/=dominant;
        }

        for (uint j=i+1;j<size;j++)
        {
            double first = matrCopy[j][i];
            for (uint k=i;k<size;k++)
            {
                matrCopy[j][k]=matrCopy[j][k] - first*matrCopy[i][k];
            }
        }
    }

    for (uint i=0;i<size;i++)
    {
        delete[] matrCopy[i];
    }
    delete[] matrCopy;
    return d*sgn;
}
Gauss::Position Gauss::findDominant(uint k, double **&matr)
{
    Position pos;
    pos.m = k;
    pos.n = k;
    for (uint i=k;k<size;k++)
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

void Gauss::swapRows(int x, int y, double **&matr, bool chVector)
{
    for (uint i=0;i<size;i++)
    {
        double tmp = matr[x][i];
        matr [x][i] = matr[y][i];
        matr [y][i] = tmp;
    }
    if (chVector)
    {
        int tmp = permutationRows[x];
        permutationRows [x] = permutationRows[y];
        permutationRows [y] = tmp;
    }
}

void Gauss::swapColumns(int x, int y, double **&matr, bool chVector)
{
    for (uint i=0;i<size;i++)
    {
        double tmp = matr[i][x];
        matr [i][x] = matr[i][y];
        matr [i][y] = tmp;
    }    
    if (chVector)
    {
        int tmp = permutationColumns[x];
        permutationColumns [x] = permutationColumns[y];
        permutationColumns [y] = tmp;
    }
}
void Gauss::permutate(double *&x)
{
    double* res = new double [size];
    for (uint i=0;i<size;i++)
    {
        res[permutationColumns[i]]=x[i];
    }
    for (uint i=0;i<size;i++)
    {
        x[i]=res[i];
    }
    delete res;
}

double** Gauss::invert()
{
    for (int i=0;i<size;i++)
    {
        permutationColumns[i]=i;
        permutationRows[i]=i;
    }
    double** matrCopy = NULL;
    copy(this->matrix,matrCopy);
    double** indent = getIndent(this->size);
    for (uint i=0;i<size;i++)
    {
        Position dominantPos = findDominant(i,matrCopy);
        double dominant = matrCopy[dominantPos.m][dominantPos.n];
        if (fabs(dominant)<pow(10,-20)) throw DivByZeroException ();
        if (dominantPos.m==i && dominantPos.n!=i)
        {
            swapColumns(i,dominantPos.n,matrCopy, true);
            swapColumns(i,dominantPos.n,indent, false);

        }
        if (dominantPos.n==i && dominantPos.m!=i)
        {
            swapRows(i,dominantPos.m, matrCopy,true);
            swapRows(i,dominantPos.m, indent,false);
        }
        for (uint j=0;j<size;j++)
        {
            matrCopy[i][j]/=dominant;
            indent[i][j]/=dominant;
        }

        for (uint j=i+1;j<size;j++)
        {
            double first = matrCopy[j][i];
            for (uint k=0;k<size;k++)
            {
                matrCopy[j][k]=matrCopy[j][k] - first*matrCopy[i][k];
                indent[j][k] = indent[j][k]-first*indent[i][k];
            }
        }
    }

    for (int i=size-1;i>=0;i--)
    {
        for (int j=i-1;j>=0;j--)
        {
            double tmp = matrCopy[j][i];
            for  (int k=0;k<size;k++)
            {
                matrCopy[j][k] = matrCopy[j][k]-matrCopy[i][k]*tmp;
                indent[j][k] = indent[j][k]-indent[i][k]*tmp;
            }
        }

    }

    for (int i=0;i<size;i++)
    {
        swapColumns(permutationColumns[i],i,indent,false);
        swapColumns(permutationColumns[i],i,matrCopy,true);
    }

    for (int i=0;i<size;i++)
    {
        for (int j=0;j<size;j++)
        {
            if (matrCopy[i][j]==1)
            {
                permutationRows[i]=j;
            }
        }
    }
    for (int i=0;i<size;i++)
    {
        swapRows(permutationRows[i],i,indent,true);
    }
    for (uint i=0;i<size;i++)
    {
        delete[] matrCopy[i];

    }
    delete[] matrCopy;
    return indent;
} 

