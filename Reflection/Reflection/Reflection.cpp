#include "Reflection.h"

Reflection::Reflection(char *filein)
{
	FILE* file_in = fopen (filein, "r");
	fscanf(file_in,"%d", &sz);
	matrix = new double* [sz];
	f = new double [sz];
	for (int i=0;i<sz;i++)
	{
		matrix[i] = new double [sz];
		for (int j=0;j<sz;j++)
		{
			fscanf(file_in,"%lf",&matrix[i][j]);
		 
		}
		fscanf(file_in,"%lf",&f[i]);
		 
	}
	fclose (file_in);
}

Reflection::~Reflection(void)
{
	for (int i=0;i<sz;i++) delete [] matrix[i];
	delete [] matrix;
	delete [] f;
}

double* Reflection::solve()
{
	double* x = new double [sz];
	for (int k=0;k<sz-1;k++)
	{
		double alpha;
		double* omega = getOmega(k, alpha);
                printf ("k=%d alpha = %.3f omega= (",k,alpha);
                for (int ii=0;ii<sz;ii++) printf ("%.3lf  ",omega[ii]);
                printf (")\n");
		matrix[k][k]=alpha;
		for (int i=0;i<sz;i++)
		{
			for (int j=0;j<sz;j++)
			{
				if (i<k)
				{
					matrix[i][j]=matrix[i][j];
				}
				if (i>=k && j>k)
				{
					double b =0;
					for (int t =0;t<sz;t++) b+=2*matrix[t][j]*omega[t]*omega[i];					
					matrix[i][j] = matrix[i][j]-b;
				}
				if (i>k && j<=k)
				{
					matrix[i][j]=0;
				}	
			}
			
			double b=0;
			for (int t=0;t<sz;t++) b+=2*f[t]*omega[t]*omega[i];
			f[i] -=b;
		}
		delete [] omega;
	}
	
	for (int i=0;i<sz;i++)
	{
		for (int j=0;j<sz;j++)
		{
			printf ("%8.3lf",matrix[i][j]);
		}
		printf ("\n");
	}
	for (int i = sz - 1; i >= 0; i--)
	{
		if(matrix[i][i] != 0)
		{
			x[i] = f[i];
			for (int j = i + 1; j < sz; j++)
			{
				x[i] -= matrix[i][j]*x[j];
			}
			x[i] = x[i]/matrix[i][i];
		}
	}


	return x;
}

double* Reflection::getOmega (int k, double& alpha)
{
	double* o = new double [sz];
	double* s = new double [sz];
	double* e = new double [sz];
	double K = 0;
	alpha =0;
	for (int i=0;i<sz;i++)
	{
		e[i]=i==k?1:0;
                s[i]=i<k?0:matrix[i][k];
		alpha+=s[i]*s[i];
	}
	alpha = pow (alpha,0.5);
	for (int i=0;i<sz;i++)
	{
		K+=s[i]*(s[i]-alpha*e[i]);
	}
	K = pow (K,-0.5);
	for (int i=0;i<sz;i++)
	{
		o[i] = K*(s[i]-alpha*e[i]);
	}
	delete [] s;
	delete [] e;
	return o;
}
