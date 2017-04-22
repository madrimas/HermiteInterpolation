#include <iostream>

using namespace std;

double* hermiteInterpolation(double* tabW, double* tabX, int size);
double value(double x, double* tabX, double* tabY, int size);

int main() {

	int size = 9;
	double tabx[] = { -1,-1,-1,0,0,0,1,1,1 };
	double taby[] = { 2,-8,56,1,0,0,2,8,56 };

	double *tablica_wspolczynnikow = new double[size];

	tablica_wspolczynnikow = hermiteInterpolation(tabx, taby, size);

	for (int i = 0; i < size; i++) {
		cout << "Wspolczynnik " << i + 1 << ": " << tablica_wspolczynnikow[i] << endl;
	}

	cout << endl;

	double krok = (tabx[size - 1] - tabx[0]) / 20;
	for (double i = tabx[0]; i <= tabx[size - 1]; i += krok)
	{
		cout << i << "\t\t" << value(i, tablica_wspolczynnikow, tabx, size) << endl;
	}


	system("pause");
	return 0;
}

double * hermiteInterpolation(double * tabX, double * tabY, int size)
{
	double* a = new double[size];
	int* pochodna = new int[size];
	a = tabY;
	for (int i = 0; i < size; i++) {
		if (tabX[i] == tabX[i - 1]) {
			pochodna[i] = pochodna[i - 1] + 1;
		}
		else {
			pochodna[i] = 0;
		}
	}

	long long silnia = 1;
	for (int i = 1; i < size; i++) {
		silnia *= i;
		for (int j = size - 1; j >= i; j--) {
			if (pochodna[j] == 0) {
				a[j] = (tabY[j] - tabY[(j - 1 - pochodna[j - 1])]) / (tabX[j] - tabX[j - i]);
			}
			else {
				a[j] /= silnia;
				pochodna[j]--;
			}
		}
	}

	return a;
}

double value(double x, double * tabW, double * tabX, int size)
{
	double val = tabW[0];
	double temp = 1;
	for (int i = 1; i < size; i++) {
		temp *= x - tabX[i - 1];
		val += tabW[i] * temp;
	}
	return val;
}
