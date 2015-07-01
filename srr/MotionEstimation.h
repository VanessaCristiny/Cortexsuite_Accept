#ifndef MOTIONESTIMATION_H
#define MOTIONESTIMATION_H

#include "App.h"
#include <enerc.h>

typedef struct MotionVector {
	APPROX double x;
	APPROX double y;
}MV;

extern MV mv[l*l];

HRESULT GetMotionVectors();
#endif
