#ifndef LDA_INFERENCE_H
#define LDA_INFERENCE_H

#include <math.h>
#include <float.h>
#include <assert.h>
#include <enerc.h>
#include "lda.h"
#include "utils.h"

APPROX float VAR_CONVERGED;
int VAR_MAX_ITER;

APPROX double lda_inference(document*, lda_model*, APPROX double*, double**);
APPROX double compute_likelihood(document*, lda_model*, double**, double*);

#endif
