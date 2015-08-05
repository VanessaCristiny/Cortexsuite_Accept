#ifndef LDA_ALPHA_H
#define LDA_ALPHA_H

#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <enerc.h>

#include "lda.h"
#include "utils.h"

#define NEWTON_THRESH 1e-5
#define MAX_ALPHA_ITER 1000

APPROX double alhood(APPROX double a, APPROX double ss, int D, int K);
APPROX double d_alhood(APPROX double a, APPROX double ss, int D, int K);
APPROX double d2_alhood(APPROX double a, int D, int K);
APPROX double opt_alpha(double ss, int D, int K);
void maximize_alpha(double** gamma, lda_model* model, int num_docs);

#endif
