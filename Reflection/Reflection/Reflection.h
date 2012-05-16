#pragma once


#include <stdio.h>
#include <cmath>
class Reflection
{
	double ** matrix;
	double* f;
	unsigned int sz;

	double* getOmega (int k, double& alpha);
	
public:
	Reflection(char* filein);
	double* solve ();
	int getSize () {return sz;}
	~Reflection(void);
};
