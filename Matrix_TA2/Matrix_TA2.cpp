// Matrix_TA2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include "time.h"
#include <omp.h>
#include <iostream>
#define N 3
#define M 3

using namespace std;

void printResult(int Matrix[N][M]){
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) cout << Matrix[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

void producto_cruz_matrices(int M1[N][M], int M2[N][M]) {
	int result[N][M] = { {0,0,0},{0,0,0},{0,0,0} };
	clock_t startPRO_C = clock();
#pragma omp parallel num_threads(N*M)
	{
		int id = omp_get_thread_num();
		int i = id % N;
		int j = id / M;
		for (int k = 0; k < N; k++)
		{
			result[i][j] = result[i][j] + M1[i][k]*M2[k][j];
		}
	}
	clock_t timeElapsed = (clock() - startPRO_C);
	unsigned msElapsed = timeElapsed;
	cout << "Resultado Producto Cruz:       DURACION " << msElapsed << " ms" << endl;
	printResult(result);
}

void producto_punto_matrices(int M1[N][M], int M2[N][M]) {
	int result[N][M] = { {0,0,0},{0,0,0},{0,0,0} };
	clock_t startPRO_P= clock();
	
#pragma omp parallel num_threads(N*N)
	{
		int id = omp_get_thread_num();
		int i = id % N;
		int j = id / N;
		for (int p = 0; p < N; p++) result[i][j] += M1[i][p] * M2[p][j];
	}
	clock_t timeElapsed = (clock()-startPRO_P);
	unsigned msElapsed = timeElapsed;
	cout << "Resultado Producto Punto:       DURACION "<< msElapsed<< " ms"<< endl;
	printResult(result);
}

void producto_numero_escalar(int M1[N][M], double E) {
	int result[N][N] = { {0,0,0},{0,0,0},{0,0,0} };
	clock_t startPRO= clock();
	
#pragma omp parallel num_threads(N*M)
	{
		int id = omp_get_thread_num();
		int i = id % N;
		int j = id / M;
		result[i][j] = M1[i][j] * E;
	}
	clock_t timeElapsed = (clock()-startPRO);
	unsigned msElapsed = timeElapsed;
	cout << "Resultado escalar por matriz:       DURACION "<< msElapsed<< " ms"<< endl;
	printResult(result);
}

void getSuma(int M1[N][M],int M2[N][M]) {
	int result[N][M] = { {0,0,0}, {0,0,0}, {0,0,0} };
	clock_t startSUM= clock();
	
#pragma omp parallel num_threads(N*M)
	{
		int id = omp_get_thread_num();
		int i = id % N;
		int j = id / M;
		result[i][j] = M1[i][j] + M2[i][j];
	}

	clock_t timeElapsed = (clock()-startSUM);
	unsigned msElapsed = timeElapsed;
	cout<<"Resultado de suma     DURACION "<< msElapsed<< " ms" <<endl;
	printResult(result);
}

void getResta(int M1[N][M], int M2[N][M]) {
	int result[N][M] = { {0,0,0},{0,0,0},{0,0,0} };
	clock_t startDIFF= clock();

#pragma omp parallel num_threads(N*M)
	{
		int id = omp_get_thread_num();
		int i = id % N;
		int j = id / M;
		result[i][j] = M1[i][j] - M2[i][j];
	}
	clock_t timeElapsed = (clock()-startDIFF);
	unsigned msElapsed = timeElapsed;
	cout << "Resultado Resta:   DURACION "<< msElapsed<< " ms" << endl;
	printResult(result);
}

int main()
{
	int M1[N][M] = { {3,4,5},{6,7,8},{6,2,2} };
	int M2[N][M] = { {1,0,1},{0,1,0},{1,0,1} };

	cout << "Matriz 1" << endl;
	printResult(M1);

	cout << "Matriz 2" << endl;
	printResult(M2);

	getSuma(M1,M2);
	getResta(M1, M2);
	producto_numero_escalar(M1,4.5);
	producto_punto_matrices(M1, M2);
	producto_cruz_matrices(M1, M2);
}
