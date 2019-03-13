#include "GaussSolve.h"


bool GaussSolve::OpenInputfile(const char* input_file_name)
{
	file_input.open(input_file_name, ios::binary);
	if (!file_input.is_open()) {
		return false;
	}
	return true;
}

bool GaussSolve::OpenOutputfile(const char* output_file_name)
{
	file_output.open(output_file_name);
	if (!file_output.is_open()) {
		return false;
	}
	return true;
}

bool GaussSolve::ErrWriteOutputFile(const char* str)
{
	if (!file_output.is_open()) {
		return false;
	}	file_output << str << endl;
	return true;
}

bool GaussSolve::ReadInputFile()
{
	if (!file_input.is_open()) {
		return false;
	}
	file_input.read((char *)&size_matr, sizeof(int));
	a = new int *[size_matr];
	for (int i = 0; i < size_matr; i++) {
		a[i] = new int[size_matr];
		file_input.read((char *)a[i], size_matr * sizeof(int));
	}
	y = new int[size_matr];
	file_input.read((char *)y, size_matr * sizeof(int));
	return true;
}

bool GaussSolve::MergerAY()
{
	s = new double *[size_matr];
	for (int i = 0; i < size_matr; i++) {
		s[i] = new double[size_matr + 1];
	}
	for (int i = 0; i < size_matr; i++) {
		for (int j = 0; j < size_matr; j++) {
			s[i][j] = (double)a[i][j];
		}
		s[i][size_matr] = (double)y[i];
	}
	return false;
}

bool GaussSolve::WriteOutputFile()
{
	if (!file_output.is_open()) {
		return false;
	}
	for (int i = 0; i < size_matr; i++) {
		file_output << x[i] << endl;
	}
	return true;
}

bool GaussSolve::Solve()
{
	MergerAY();

	x = new double[size_matr];
	for (int i = 0; i < size_matr; i++) {
		x[i] = 0;
	}
	double tmp;
	//Поиск максимального элемента в столбце
	for (int k = 0; k < size_matr; k++) 
	{
		tmp = abs(s[k][k]);
		int i = k;
		for (int m = k + 1; m < size_matr; m++)
			if (abs(s[m][k]) > tmp)
			{
				i = m;
				tmp = abs(s[m][k]);
			}

		if (tmp == 0)
		{
			return false;
		}

		if (i != k){
			SwapLines(i, k);
		}

		tmp = s[k][k];
		s[k][k] = 1;
		for (int j = k + 1; j < size_matr + 1; j++)
			s[k][j] = s[k][j] / tmp;

		TransformLine(k);
	}
	SolveSLAY();
	return true;
}

bool GaussSolve::SolveSLAY()
{
	for (int i = size_matr - 1; i >= 0; i--)
	{
		x[i] = 0;
		double tmp = s[i][size_matr];
		for (int j = size_matr - 1; j > i; j--)
			tmp = tmp - s[i][j] * x[j];
		x[i] = tmp;
	}
	return true;
}

bool GaussSolve::SwapLines(int line1, int line2)
{
	for (int j = line2; j < size_matr + 1; j++)
	{
		double tmp = s[line2][j];
		s[line2][j] = s[line1][j];
		s[line1][j] = tmp;
	}
	return true;
}

bool GaussSolve::TransformLine(int line)
{
	for (int i = line + 1; i < size_matr; i++)
	{
		double tmp = s[i][line];
		s[i][line] = 0;
		if (tmp != 0)
			for (int j = line + 1; j < size_matr + 1; j++)
				s[i][j] = s[i][j] - tmp * s[line][j];
	}
	return false;
}

GaussSolve::GaussSolve()
{
}


GaussSolve::~GaussSolve()
{
	file_input.close();
	file_output.close();
	for (int i = 0; i < size_matr; i++) {
		delete[]a[i];
	}
	delete[]a;
	delete[]y;
	for (int i = 0; i < size_matr; i++) {
		delete[]s[i];
	}
	delete[]s;
	delete[]x;
}
