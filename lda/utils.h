#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <enerc.h>

APPROX double log_sum(APPROX double log_a, APPROX double log_b);
APPROX double trigamma(APPROX double x);
APPROX double digamma(APPROX double x);
APPROX double log_gamma(APPROX double x);
void make_directory(char* name);
int argmax(double* x, int n);

#endif
