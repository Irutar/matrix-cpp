#ifndef __Matrix_H__
#define __Matrix_H__
#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;

class Exception
{
public:
  const char* msg;
  Exception(const char* arg)
   : msg(arg)
  {
  }
};

class Matrix
{
	struct rcMatrix;
	rcMatrix* data;
public:
class Range{};
class Cref{};
Matrix();
Matrix(const double& v);
Matrix(const int row_count, const int column_count);
Matrix(const char FilePath[]);
Matrix(const Matrix& a);
~Matrix();
friend ostream & operator << (ostream & s, const Matrix & a);
Matrix& operator= (const Matrix& a);
Matrix& operator= (const double& v);
Matrix& operator+ (const Matrix& a);
Matrix& operator+ (const double& v);
Matrix& operator+= (const Matrix& a);
Matrix& operator+= (const double& v);
Matrix& operator- (const Matrix& a);
Matrix& operator- (const double& v);
Matrix& operator-= (const Matrix& a);
Matrix& operator-= (const double& v);
Matrix& operator* (const Matrix& a);
Matrix& operator* (const double& v);
Matrix& operator*= (const Matrix& a);
Matrix& operator*= (const double& v);
bool operator == (const Matrix& a);
double& operator()(const int r, const int c);
};

struct Matrix::rcMatrix
{
	double** p;
	int rows;
	int cols;
	unsigned int n;

	rcMatrix()
	{
		n = 1;
		p = NULL;
		rows = 0;
		cols = 0;
	}

	rcMatrix(const double& v)
	{
		n = 1;
		rows = 1;
		cols = 1;
		p = new double*[rows];
		for (int r = 0; r < rows; r++)
		{
			p[r] = new double[cols];
			for (int c = 0; c < cols; c++)
			{
				p[r][c] = v;
			}
		}
	}

rcMatrix(const int row_count, const int column_count)
{
	n = 1;
	p = NULL;

	if (row_count > 0 && column_count > 0)
	{
		rows = row_count;
		cols = column_count;

		p = new double*[rows];
		for (int r = 0; r < rows; r++)
		{
			p[r] = new double[cols];
			// initially fill in zeros for all values in the matrix;
			for (int c = 0; c < cols; c++)
			{
				p[r][c] = 0;
			}
		}
	}
};

rcMatrix(const char FilePath[])
{
	//create a matrix from a file
	ifstream in(FilePath);
	if (!in)
	{
		cout << "Cannot open file.\n";
		return;
	}

	in >> rows;
	in >> cols;

	n = 1;
	p = new double*[rows];
	for (int i = 0 ; i < rows ; i++)
	{
	    p[i] = new double[cols];
	}

	for (int i=0 ; i < rows ; i++)
	{
		for (int j=0; j < cols; j++)
		{
			in>>p[i][j];
		}
	}

	in.close();
	}

	void assign(Matrix a)
	{
		if(rows != a.data->rows || cols != a.data->cols)
		{
			double** np;
			np = new double* [a.data->rows];
			for(int i = 0; i < a.data->rows; i++)
			{
				np[i] = new double [a.data->cols];
			}

			for (int r = 0; r < a.data->rows; r++)
			{
				for (int c = 0; c < a.data->cols; c++)
				{
					np[r][c] = a.data->p[r][c];
				}
			}
			for(int i=0; i< rows; i++)
			{
				delete[] p[i];
			}
			delete[] p;
			rows = a.data->rows;
			cols = a.data->cols;
			p=np;
		}
		else
		{
			p = a.data->p;
		}
	}

	~rcMatrix()
	{
		for (int r = 0; r < rows; r++)
		{
      		delete[] p[r];
    	}
    	delete[] p;
	}
};

inline Matrix::Matrix()
{
	data = new rcMatrix();
}

inline Matrix::Matrix(const double& v)
{
	data = new rcMatrix(v);
}

inline Matrix::Matrix(const int row_count, const int column_count)
{
	data = new rcMatrix(row_count, column_count);
}

inline Matrix::Matrix(const char FilePath[])
{
	data = new rcMatrix(FilePath);
}

inline Matrix::Matrix(const Matrix& a)
{
	a.data->n++;
	data=a.data;
}

inline Matrix::~Matrix()
{
	if(--data->n == 0)
	{
		cout << "delete data" << endl;
		delete data;
	}
}

ostream& operator << (ostream& s, const Matrix& a)
{
	if (a.data->p != NULL)
	{
		s << "[";
		for (int r = 0; r < a.data->rows; r++)
		{
			if (r > 0)
			{
				s << " ";
			}
			for (int c = 0; c < a.data->cols-1; c++)
			{
				s << a.data->p[r][c] << ", ";
			}
			if (r < a.data->rows-1)
			{
				s << a.data->p[r][a.data->cols-1] << "\n";
			}
			else
			{
				s << a.data->p[r][a.data->cols-1] << "]\n";
			}
		}
	}
	else
	{
		// matrix is empty
		s << "[ ]";
	}
	return s;
}

Matrix& Matrix::operator= (const Matrix& a)
{
	if(data->n == 1)
	{
		data->assign(a);
	}
	else
	{
		rcMatrix* np = new rcMatrix(a.data->rows, a.data->cols);
		for (int r = 0; r < a.data->rows; r++)
		{
			for (int c = 0; c < a.data->cols; c++)
			{
				np->p[r][c] = a.data->p[r][c];
			}
		}
		data->n--;
		data = np;
	}
	return *this;
}

Matrix& Matrix::operator= (const double& v)
{
	if(data->n == 1)
	{
		for (int r = 0; r < data->rows; r++)
		{
			for (int c = 0; c < data->cols; c++)
			{
				data->p[r][c] = v;
			}
		}
	}
	else if(data->n == 0)
	{
		rcMatrix* np = new rcMatrix(v);
		data->n++;
		data = np;
	}
	else
	{
		rcMatrix* np = new rcMatrix(data->rows, data->cols);
		for (int r = 0; r < data->rows; r++)
		{
			for (int c = 0; c < data->cols; c++)
			{
				np->p[r][c] = v;
			}
		}
		data->n--;
		data = np;
	}
	return *this;
}

inline Matrix& Matrix::operator+= (const Matrix& a)
{
	if(data->rows == a.data->rows && data->cols == a.data->cols)
	{
		if (data->n == 1)
		{
			for (int r = 0; r < a.data->rows; r++)
			{
				for (int c = 0; c < a.data->cols; c++)
				{
				  data->p[r][c] += a.data->p[r][c];
				}
			}
			return *this;
		}
		else
		{
			rcMatrix* np = new rcMatrix(data->rows, data->cols);
			for (int r = 0; r < data->rows; r++)
			{
				for (int c = 0; c < data->cols; c++)
				{
					np->p[r][c] += a.data->p[r][c];
				}
			}
			data->n--;
			data = np;
			return *this;
		}
	}
	else
	{
		throw Exception("Dimensions does not match");
    }
}

inline Matrix& Matrix::operator+= (const double& v)
{
	if (data->n == 1)
	{
		for (int r = 0; r < data->rows; r++)
		{
			for (int c = 0; c < data->cols; c++)
			{
			  data->p[r][c] += v;
			}
		}
		return *this;
	}
	else
	{
		rcMatrix* np = new rcMatrix(data->rows, data->cols);
		for (int r = 0; r < data->rows; r++)
		{
			for (int c = 0; c < data->cols; c++)
			{
				np->p[r][c] = v;
			}
		}
		data->n--;
		data = np;
		return *this;
	}
}

inline Matrix& Matrix::operator + (const Matrix& a)
{
	if(data->rows == a.data->rows && data->cols == a.data->cols)
	{
		if (data->n == 1)
		{
			for (int r = 0; r < a.data->rows; r++)
			{
				for (int c = 0; c < a.data->cols; c++)
				{
				  data->p[r][c] += a.data->p[r][c];
				}
			}
			return *this;
		}
		else
		{
			rcMatrix* np = new rcMatrix(data->rows, data->cols);
			for (int r = 0; r < data->rows; r++)
			{
				for (int c = 0; c < data->cols; c++)
				{
					np->p[r][c] += a.data->p[r][c];;
				}
			}
			data->n--;
			data = np;
			return *this;
		}
	}
	else
	{
		throw Exception("Dimensions does not match");
    }
}

inline Matrix& Matrix::operator + (const double& v)
{
	if (data->n == 1)
	{
		for (int r = 0; r < data->rows; r++)
		{
			for (int c = 0; c < data->cols; c++)
			{
			  data->p[r][c] += v;
			}
		}
		return *this;
	}
	else
	{
		rcMatrix* np = new rcMatrix(data->rows, data->cols);
		for (int r = 0; r < data->rows; r++)
		{
			for (int c = 0; c < data->cols; c++)
			{
				np->p[r][c] += v;;
			}
		}
		data->n--;
		data = np;
		return *this;
	}
}

inline Matrix& Matrix::operator-= (const Matrix& a)
{
	if(data->rows == a.data->rows && data->cols == a.data->cols)
	{
		if (data->n == 1)
		{
			for (int r = 0; r < a.data->rows; r++)
			{
				for (int c = 0; c < a.data->cols; c++)
				{
				  data->p[r][c] -= a.data->p[r][c];
				}
			}
			return *this;
		}
		else
		{
			rcMatrix* np = new rcMatrix(data->rows, data->cols);
			for (int r = 0; r < data->rows; r++)
			{
				for (int c = 0; c < data->cols; c++)
				{
					np->p[r][c] -= a.data->p[r][c];
				}
			}
			data->n--;
			data = np;
			return *this;
		}
	}
	else
	{
		throw Exception("Dimensions does not match");
    }
}

inline Matrix& Matrix::operator-= (const double& v)
{
	if (data->n == 1)
	{
		for (int r = 0; r < data->rows; r++)
		{
			for (int c = 0; c < data->cols; c++)
			{
			  data->p[r][c] -= v;
			}
		}
		return *this;
	}
	else
	{
		rcMatrix* np = new rcMatrix(data->rows, data->cols);
		for (int r = 0; r < data->rows; r++)
		{
			for (int c = 0; c < data->cols; c++)
			{
				np->p[r][c] = (-v);
			}
		}
		data->n--;
		data = np;
		return *this;
	}
}

inline Matrix& Matrix::operator - (const Matrix& a)
{
	if(data->rows == a.data->rows && data->cols == a.data->cols)
	{
		if (data->n == 1)
		{
			for (int r = 0; r < a.data->rows; r++)
			{
				for (int c = 0; c < a.data->cols; c++)
				{
				  data->p[r][c] -= a.data->p[r][c];
				}
			}
			return *this;
		}
		else
		{
			rcMatrix* np = new rcMatrix(data->rows, data->cols);
			for (int r = 0; r < data->rows; r++)
			{
				for (int c = 0; c < data->cols; c++)
				{
					np->p[r][c] -= a.data->p[r][c];;
				}
			}
			data->n--;
			data = np;
			return *this;
		}
	}
	else
	{
		throw Exception("Dimensions does not match");
    }
}

inline Matrix& Matrix::operator - (const double& v)
{
	if (data->n == 1)
	{
		for (int r = 0; r < data->rows; r++)
		{
			for (int c = 0; c < data->cols; c++)
			{
			  data->p[r][c] -= v;
			}
		}
		return *this;
	}
	else
	{
		rcMatrix* np = new rcMatrix(data->rows, data->cols);
		for (int r = 0; r < data->rows; r++)
		{
			for (int c = 0; c < data->cols; c++)
			{
				np->p[r][c] -= v;;
			}
		}
		data->n--;
		data = np;
		return *this;
	}
}

inline Matrix& Matrix::operator*= (const double& v)
{
	if (data->n == 1)
	{
		for (int r = 0; r < data->rows; r++)
		{
			for (int c = 0; c < data->cols; c++)
			{
			  data->p[r][c] *= v;
			}
		}
		return *this;
	}
	else
	{
		rcMatrix* np = new rcMatrix(data->rows, data->cols);
		for (int r = 0; r < data->rows; r++)
		{
			for (int c = 0; c < data->cols; c++)
			{
				np->p[r][c] *= v;
			}
		}
		data->n--;
		data = np;
		return *this;
	}
}

inline Matrix& Matrix::operator * (const double& v)
{
	if (data->n == 1)
	{
		for (int r = 0; r < data->rows; r++)
		{
			for (int c = 0; c < data->cols; c++)
			{
			  data->p[r][c] *= v;
			}
		}
		return *this;
	}
	else
	{
		rcMatrix* np = new rcMatrix(data->rows, data->cols);
		for (int r = 0; r < data->rows; r++)
		{
			for (int c = 0; c < data->cols; c++)
			{
				np->p[r][c] *= v;;
			}
		}
		data->n--;
		data = np;
		return *this;
	}
}

inline Matrix& Matrix::operator*= (const Matrix& a)
{
	if(data->cols == a.data->rows)
	{
		if (data->n == 1)
		{
			rcMatrix* np = new rcMatrix(data->rows, a.data->cols);
			for (int r = 0; r < data->rows; r++)
			{
				for (int c_a = 0; c_a < a.data-> cols; c_a++)
				{
					for (int c = 0; c < data->cols; c++)
					{
					  np->p[r][c_a] += data->p[r][c] * a.data->p[r][c_a];
					}
				}
			}
			for(int i=0; i< data->rows; i++)
			{
				delete[] data->p[i];
			}
			delete[] data->p;
			data = np;
			return *this;
		}
		else
		{
			rcMatrix* np = new rcMatrix(data->rows, a.data->cols);
			for (int r = 0; r < data->rows; r++)
			{
				for (int c_a = 0; c_a < a.data-> cols; c_a++)
				{
					for (int c = 0; c < data->cols; c++)
					{
					  np->p[r][c_a] += data->p[r][c] * a.data->p[r][c_a];
					}
				}
			}
			data->n--;
			for(int i=0; i < data->rows; i++)
			{
				delete[] data->p[i];
			}
			delete[] data->p;
			data = np;
			return *this;
		}
	}
	else
	{
		throw Exception("Dimensions does not match");
    }
}

inline Matrix& Matrix::operator* (const Matrix& a)
{
	if(data->cols == a.data->rows)
	{
		if (data->n == 1)
		{
			rcMatrix* np = new rcMatrix(data->rows, a.data->cols);
			for (int r = 0; r < data->rows; r++)
			{
				for (int c_a = 0; c_a < a.data-> cols; c_a++)
				{
					for (int c = 0; c < data->cols; c++)
					{
					  np->p[r][c_a] += data->p[r][c] * a.data->p[r][c_a];
					}
				}
			}
			for(int i=0; i< data->rows; i++)
			{
				delete[] data->p[i];
			}
			delete[] data->p;
			data = np;
			return *this;
		}
		else
		{
			rcMatrix* np = new rcMatrix(data->rows, a.data->cols);
			for (int r = 0; r < data->rows; r++)
			{
				for (int c_a = 0; c_a < a.data-> cols; c_a++)
				{
					for (int c = 0; c < data->cols; c++)
					{
					  np->p[r][c_a] += data->p[r][c] * a.data->p[r][c_a];
					}
				}
			}
			data->n--;
			for(int i=0; i < data->rows; i++)
			{
				delete[] data->p[i];
			}
			delete[] data->p;
			data = np;
			return *this;
		}
	}
	else
	{
		throw Exception("Dimensions does not match");
    }
}

inline bool Matrix::operator == (const Matrix& a)
{
	if(data->rows != a.data->rows || data->cols != a.data->cols)
	{
		return false;
	}
	for (int r = 0; r < a.data->rows; r++)
	{
		for (int c = 0; c < a.data->cols; c++)
		{
		 	if (data->p[r][c] != a.data->p[r][c])
		 	{
				return false;
			}
		}
	}
	return true;
}

double& Matrix::operator()(const int r, const int c)
{
	if (data->p != NULL && r > 0 && r <= data->rows && c > 0 && c <= data->cols)
	{
		return data->p[r-1][c-1];
	}
	else
	{
		throw Exception("Subscript out of range");
	}
}

#endif /* __Matrix_H__ */
