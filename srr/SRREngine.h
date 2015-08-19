#ifndef SRRENGINE_H
#define SRRENGINE_H

#include "App.h"
#include "MotionEstimation.h"
#define ALPHA 2.5

extern double*** f;

void MatMul (APPROX double** mat1, double mat2[], APPROX double result[]);
void MatMul_ (APPROX double** mat1, APPROX double** mat2, APPROX double result[(l*l)][(l*l)]);
void MatAdd(double mat1[],double mat2[]);
void MatSub(double mat1[],double mat2[], double res[]);
//void Invert2(double *mat, double *dst);
void GaussSeidel(APPROX double** A1, APPROX double* X, APPROX double* Y);
void Gauss(int rn, int pn);
void get_g(int rn,int pn);
void flush_b();
void flush_arr(double temp[]);
void get_b(int rn);
void modify_b(int rn, int pn);
void solve_pixel(int rn, int pn);
void solve_row(int rn);
HRESULT SRREngine123();
#endif
