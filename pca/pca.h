#include <enerc.h>

#ifndef PCA_H
#define PCA_H

void corcol(APPROX float **data, int n, int m, APPROX float **symmat);

void covcol(APPROX float **data, int n, int m, APPROX float **symmat);

void scpcol(APPROX float **data, int n, int m, APPROX float **symmat);

void erhand(char err_msg[]);

APPROX float *vector(int n);

float **matrix(int n, int m);

void free_vector(float *v, int n);

void free_matrix(APPROX float **mat, int n, int m);

void tred2(APPROX float **a, int n, APPROX float *d, APPROX float *e);

void tqli(APPROX float d[], APPROX float e[], int n, APPROX float **z);


#endif