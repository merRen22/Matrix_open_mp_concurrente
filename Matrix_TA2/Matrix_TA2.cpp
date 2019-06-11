// Matrix_TA2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include <omp.h>
#include <iostream>
#define N 3
#define M 3

using namespace std;

int main()
{
	int M1[N][M] = { {3,4,5},{6,7,8},{6,2,2} };
	int M2[N][M] = { {1,0,1},{0,1,0},{1,0,1} };

	getSuma(M1,M2);
	getResta(M1, M2);
}

void getSuma(int M1[N][M],int M2[N][M]) {
	int result[N][M] = { {0,0,0}, {0,0,0}, {0,0,0} };
	
#pragma omp parallel num_threads(N*M)
	{
		int id = omp_get_thread_num();
		int i = id % N;
		int j = id % M;
		result[i][j] = M1[i][j] + M2[i][j];
	}

	cout<<"Resultado de suma" <<endl;
	printResult(result);
}

void getResta(int M1[N][M], int M2[N][M]) {
	int result[N][M] = { {0,0,0},{0,0,0},{0,0,0} };

#pragma omp parallel num_threads(N*M)
	{
		int id = omp_get_thread_num();
		int i = id % N;
		int j = id / M;
		result[i][j] = M1[i][j] - M2[i][j];
	}
	cout << "Resultado Resta:" << endl;
	printResult(result);
}


void multi_escalar(int A[N][N], double E) {
	int C[N][N] = { {0,0,0},{0,0,0},{0,0,0} };
#pragma omp parallel num_threads(N*N)
	{
		int id = omp_get_thread_num();
		int i = id % N;
		int j = id / N;
		C[i][j] = A[i][j] * E;
	}
	cout << "Resultado Multi. Escalar:" << endl;
	printResult(C);
}
void producto_punto(int A[N][N], int B[N][N]) {
	int C[N][N] = { {0,0,0},{0,0,0},{0,0,0} };
#pragma omp parallel num_threads(N*N)
	{
		int id = omp_get_thread_num();
		int i = id % N;
		int j = id / N;
		for (int p = 0; p < N; p++) C[i][j] += A[i][p] * B[p][j];
	}
	cout << "Resultado Producto Punto:" << endl;
	printResult(C);
}
void producto_cruz(int A[N][N], int B[N][N]) {
	int C[N][N] = { {0,0,0},{0,0,0},{0,0,0} };
#pragma omp parallel num_threads(N*N)
	{
		int id = omp_get_thread_num();
		int i = id % N;
		int j = id / N;
		// ...
	}
	cout << "Resultado Producto Cruz:" << endl;
	printResult(C);
}

void printResult(int Matrix[N][M]){
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) cout << Matrix[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}
