#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <cstdio>
#include <string>
#include "matrix.h"

using namespace std;


int main()
{
try{
	Matrix B("matrixB.dat");
	Matrix D("matrixD.dat");
	Matrix C("matrixC.dat");
	Matrix E("matrixE.dat");
 	Matrix A;
	cout << A;
	cout << C; 
	cout << B;
	A = B * C;
	B = B - D;	
	B = B + D;
	B += D;
	B -= D;
	B -= D += D;
	cout << A;
	B = B * C;
	Matrix A1;
	A1 = D - D;
	cout << "Should be all 0 below \n";
	cout << A1;
	Matrix A2;
	A2 = E + E;
	cout << A2;
	A2 += E;
	cout << A2;
	
}
	catch(Exception&)
	{
		cout << "Index Out of Range" << endl;
	}

}

