#include "Reflection.h"

int main ()
{
	Reflection ref = Reflection("input.txt");
	double* x = ref.solve();
	for (int i=0;i<ref.getSize();i++)
	{
		printf ("%7.3f",x[i]);
	}
	printf ("\n");
}