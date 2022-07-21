#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <cstdio>
#include <string>
#include "matrix.h"

using namespace std;
/*
int main()
{
//	try
//	{
		//cout << endl;

	  	Matrix A1(2,5,1.0);			//Create matrix A1 = [	1.0  0.0  0.0  0.0  0.0
							//			0.0  1.0  0.0  0.0  0.0  ]
		cout << A1 << endl;
	
		Matrix A2(5,3,0.0,6.3);		//Create matrix A1 = [	0.0  6.3  6.3 
							//			6.3  0.0  6.3 
							//			6.3  6.3  0.0
							//			6.3  6.3  6.3
							//			6.3  6.3  6.3  ]
		cout << A2 << endl;
		
		Matrix S = A1 * A2;			//Multiply A1 by A2
		cout << S << endl;
*/	
//		fstream f1;
//		f1.open("matrix.dat", fstream::in);
//		Matrix B("matrix.dat");				//Read the matrix data from file matrix.dat
//		f1.close();				//First two values in this file specify the matrix dimensions
//		cout << B << endl;
/*		
		S = B;						//Assign B to S
		S[0][0] = 1.4;					//Modify S
		cout << "S[0][0]=" << S[0][0] << endl;		//Verify S
		cout << "B[0][0]=" << B[0][0] << endl;		//Verify B
	*/
//	}
/*	catch(IndexOutOfRange&)
	{
		cout << "Index Out of Range" << endl;
	}
	catch(WrongDim&)
	{
		cout << "Wrong Matrix Dimensions" << endl;
	}
	catch(OutOfMem&)
	{
		cout << "Out of Memory" << endl;
	}
	*/ 
//}

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
//	B = B - D;	
//	B = B + D;
//	B += D;
//	B -= D;
//	B -= D += D;
	cout << A;
//	B = B * C;
	Matrix A1;
	A1 = D - D;
	cout << "Should be all 0 below \n";
	cout << A1;
	Matrix A2;
	A2 = E + E;
	cout << A2;
	A2 += E;
	cout << A2;
	
/*
	if (B == D)
		cout<<"dziala\n";
	if (B == C)
		cout<<"nie dziala\n";
	*/
//	double f;
//	f=B(1,2);
//	cout<<f<<endl;
}
	catch(Exception&)
	{
		cout << "Index Out of Range" << endl;
	}
/*
try{
	Matrix B("Cities.txt");
	Matrix C("Cities2.txt");
	B = B + C;
}
	catch(Exception&)
	{
		cout << "Index Out of Range" << endl;
	}
*/	
}

