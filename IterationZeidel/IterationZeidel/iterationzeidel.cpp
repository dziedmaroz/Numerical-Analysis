#include "iterationzeidel.h"

IterationZeidel::IterationZeidel(char *filename)
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
        matrix[i][size]*=-1;
    }
    x0 = new double [size];

    for (int i=0;i<size;i++)
    {
        fscanf (fin,"%lf",&x0[i]);
    }
    fscanf (fin,"%lf",&epsilon);
    permutation = new int [size];
    for (int i=0;i<size;i++)
    {
        permutation[i]=i;
    }
    fclose (fin);
}

IterationZeidel::~IterationZeidel()
{
    for (int i=0;i<size;i++)
    {
        delete [] matrix[i];
    }
    delete [] matrix;
    delete [] x0;
    delete [] permutation;
}

void IterationZeidel::makeIterable()
{    
    for (int i=0;i<size;i++)
    {

        Position dominantPos = findDominant(i);
        double dominant = matrix[dominantPos.m][dominantPos.n];
        if (fabs(dominant)<pow(10,-20)) throw DivByZeroException ();


        if (dominantPos.m != dominantPos.n)
        {
            if (dominantPos.m==i)
            {
                swapColumns(i,dominantPos.n);
            }
            if (dominantPos.n==i)
            {
                swapRows(i,dominantPos.m);
            }
        }

        for (int j=0;j<size;j++)
        {
            if (i==j)
            {
                matrix[i][j] = 0;
            }
            else
            {
                matrix[i][j]/=-dominant;
            }
        }
        matrix[i][size]/=dominant;

    }     
}

IterationZeidel::Position IterationZeidel::findDominant(int k)
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


double IterationZeidel::normVector(double *vector, int sz)
{
    double norm = 0;
    for (int i=0;i<sz;i++)
    {
        norm += (vector[i]*vector[i]);
    }
    return pow(norm,0.5);
}

void IterationZeidel::swapRows(int x, int y)
{

    for (int i=0;i<size+1;i++)
    {
        double tmp = matrix[x][i];
        matrix [x][i] = matrix[y][i];
        matrix [y][i] = tmp;
    }

}

void IterationZeidel::swapColumns(int x, int y)
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

double* IterationZeidel::solveIteration()
{    

    double* xK = new double [size];
    for (int i=0;i<size;i++)
    {
        xK[i]=x0[i];
    }

    for (int i=0;i<size;i++)
    {
        double tmp = xK[i];
        xK[i]=xK[permutation[i]];
        xK[permutation[i]]=tmp;
    }
    double* xKnxt = new double [size];
    double* xDiff = new double [size];   
    int k=0;
    while (normVector(xDiff,size)>epsilon || k==0 )
    {
        k++;
        for (int i=0;i<size;i++)
        {
            xKnxt[i]=matrix[i][size];
            for (int j=0;j<size;j++)
            {
                xKnxt[i]+=xK[j]*matrix[i][j];
            }
        }
        for (int i=0;i<size;i++)
        {
            xDiff[i]=xK[i]-xKnxt[i];
            xK[i]=xKnxt[i];
        }


    }
    printf ("SIMPLE ITERATION:\n");
    printf ("K = %d\n",k);
    for (int i=0;i<size;i++)
    {
        double tmp = xKnxt[i];
        xKnxt[i]=xKnxt[permutation[i]];
        xKnxt[permutation[i]]=tmp;
    }
    for (int i=0;i<size;i++)
    {
        printf ("%5.3f ",xKnxt[i]);
    }
    printf ("\n");

    delete [] xKnxt;
    delete [] xK;
    delete [] xDiff;
    return NULL;
}

double* IterationZeidel::solveZeidel()
{
    double* xK = new double [size];
    for (int i=0;i<size;i++)
    {
        xK[i]=x0[i];
    }

    for (int i=0;i<size;i++)
    {
        double tmp = xK[i];
        xK[i]=xK[permutation[i]];
        xK[permutation[i]]=tmp;
    }
    double* xKnxt = new double [size];
    double* xDiff = new double [size];  
    int k=0;
    while (normVector(xDiff,size)>epsilon || k==0)
    {
        k++;
        for (int i=0;i<size;i++)
        {
            xKnxt[i]=matrix[i][size];
            for (int j=0;j<size;j++)
            {
                if (j<i)
                {
                    xKnxt[i]+=xKnxt[j]*matrix[i][j];
                }
                else
                {
                    xKnxt[i]+=xK[j]*matrix[i][j];
                }
            }
        }
        for (int i=0;i<size;i++)
        {
            xDiff[i]=xK[i]-xKnxt[i];
            xK[i]=xKnxt[i];
        }


    }
    printf ("ZEIDEL:\n");
    printf ("K = %d\n",k);
    for (int i=0;i<size;i++)
    {
        double tmp = xKnxt[i];
        xKnxt[i]=xKnxt[permutation[i]];
        xKnxt[permutation[i]]=tmp;
    }
    for (int i=0;i<size;i++)
    {
        printf ("%5.3f ",xKnxt[i]);
    }
    printf ("\n");

    delete [] xKnxt;
    delete [] xK;
    delete [] xDiff;
    return NULL;
}
