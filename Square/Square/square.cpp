#include "square.h"

Square::Square(char* filename)
{
    FILE* fin = fopen(filename,"r");
    fscanf (fin,"%d",&sz);
    matrix_ = new double* [sz];
    f = new double [sz];
    for (int i=0;i<sz;i++)
    {
        matrix_[i] = new double [sz];
        for (int j=0;j<sz;j++)
        {
            fscanf(fin,"%lf",&matrix_[i][j]);
        }
        fscanf (fin,"%lf", &f[i]);
    }
    fclose (fin);
}

Square::~Square()
{
    delete [] f;
    for (int i=0;i<sz;i++)
        delete [] matrix_[i];
    delete [] matrix_;
}

double Square::sgn(double x)
{
    if (x==0) return 0;
    return x>0?1:-1;
}

double* Square::solve()
{
    double** S = new double* [sz];
    double* D = new double[sz];
    for (int i=0;i<sz;i++)
    {
        S[i] = new double [sz];
        for (int j=i;j<sz;j++)
        {
            if (i==j)
            {
                double summ = 0;
                for (int k = 0; k<i;k++)
                {
                    summ+=S[k][i]*S[k][i]*D[k];
                }
                D[i] = sgn (matrix_[i][j]-summ);
                S[i][j]=fabs(pow (summ,0.5)-matrix_[i][j]);

            }
            if (i<j)
            {
                double summ = 0;
                for (int k=0;k<i;k++)
                {
                    summ+=S[k][i]*D[k]*S[k][j];
                }
                S[i][j] = (matrix_[i][j] - summ)/(S[i][i]*D[i]);
            }
            if (i>j)
            {
                S[i][j] = 0;
            }
        }
    }

    double* y = new double [sz];
    for (int i =0; i<sz;i++)
    {
        double summ = 0;
        for (int k=0;k<i;k++)
        {
            summ+=S[k][i]*y[k];
        }
        y[i] = (f[i] - summ)/S[i][i];
    }

    double* x = new double [sz];
    for (int i=sz-1;i>=0;i--)
    {
        double summ = 0;
        for (int k =i+1; k<sz;k++)
        {
            summ+=D[k]*S[k][i]*x[k];
        }
        x[i]=(y[i] - summ)/D[i]*S[i][i];
    }

    delete [] y;
    for (int i=0;i<sz;i++)
    {
        delete [] S[i];
    }
    delete [] D;
    delete [] S;
    return x;



}
