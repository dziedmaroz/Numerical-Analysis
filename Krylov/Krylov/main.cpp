#include <cstdlib>
#include <iostream>
#include "krylov.h"
#include <math.h>
#include <gsl/gsl_poly.h>

using namespace std;

double const E = 0.00000000001;

int main(int argc, char *argv[])
{
    for (int i=1;i<argc;i++)
    {
        printf ("RUNNING ON TEST: %s\n",argv[i]);
        Krylov krylov =  Krylov(argv[i]);
        double * poly = NULL;

        poly = krylov.getPoly ();
        if (poly==NULL)
        {
            printf ("Some errors on getPoly\n");
            return 200;
        }
        printf ("t^%d ",krylov.getSize ());
        for (int i=0;i<krylov.getSize();i++)
        {
            if (fabs(poly[i])<E) continue;
            if (poly[i]<0) printf ("+");
            if (i==krylov.getSize ()-1)
            {
                printf ("%12.6lf ",-1*poly[i]);
            }
            else
                if (i==krylov.getSize ()-2)
                {
                    printf ("%12.6lf*t ",-1*poly[i]);
                }
                else
                {
                     printf ("%12.6lf*t^%d ",-1*poly[i],krylov.getSize ()-i-1);
                }

        }
        printf ("\n");
        printf ("roots([1, ");
        for (int i=0;i<krylov.getSize ();i++)
        {
            printf ("%12.6lf",-1*poly[i]);
            if (i!=krylov.getSize ()-1) printf (", ");
            else printf (" ");
        }
        printf ("])\n");
        double* eigenVal = new double [krylov.getSize ()];
        for (int i=0;i<krylov.getSize ();i++)
        {
            printf("l%d = ",i+1);
            scanf("%lf",&eigenVal[i]);
        }

        for (int i=0;i<krylov.getSize ();i++)
        {
            double* eigenVector = krylov.getEigenVector(poly,eigenVal[i]);
            printf ("EigenValue: %12.6lf  EigenVector: (\t",eigenVal[i]);
            for (int j=0;j<krylov.getSize ();j++) printf ("%5.3lf  ",eigenVector[j]);
            printf (")\n");
            delete [] eigenVector;
        }

        delete[] poly;
    }
    return 0;

}
