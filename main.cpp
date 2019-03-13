#include <iostream>
#include "GaussSolve.h"

using namespace std;

int main()
{
	char *file_input_Name = new char[100];
	char *file_output_Name = new char[100];

	cout << "Input file: ";
	cin >> file_input_Name;
	
	cout << "Output file: ";
	cin >> file_output_Name;
	GaussSolve solve;

	if (!solve.OpenOutputfile(file_output_Name)) {
		cout << "Open fail: Output file is not open" << endl;
		return 1;
	}

	if (!solve.OpenInputfile(file_input_Name)) {
		if (!solve.ErrWriteOutputFile("Open fail: Input file is not open")) {
			cout << "Open fail: Input file is not open" << endl;
		}
		return 1;
	}

	if (!solve.ReadInputFile()) {
		if (!solve.ErrWriteOutputFile("Read fail: Input file is not open")) {
			cout << "Read fail: Input file is not open" << endl;
		}
		return 1;
	}

	if (!solve.Solve()) {
		if (!solve.ErrWriteOutputFile("The system has no solution")) {
			cout << "Solve fail: The system has no solution" << endl;
			cout << "Solve fail: Output file is not open" << endl;
		}
		return 1;
	}

	if (!solve.WriteOutputFile()) {
		cout << "Write fail: Output file is not open" << endl;
		return 1;
	}
	return 0;
}
