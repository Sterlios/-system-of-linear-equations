#pragma once
#include <fstream>
using namespace std;
class GaussSolve
{
	int size_matr;
	int*y;
	int **a;
	double *x;
	double **s;
	ifstream file_input;
	ofstream file_output;

	bool MergerAY();
	bool SolveSLAY();
	bool SwapLines(int i, int k);
	bool TransformLine(int line);

public:
	bool Solve();
	bool OpenInputfile(const char* input_file_name);
	bool OpenOutputfile(const char* output_file_name);
	bool ErrWriteOutputFile(const char* str);
	bool WriteOutputFile();
	bool ReadInputFile();
	GaussSolve();
	~GaussSolve();
};
