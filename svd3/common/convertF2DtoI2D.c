#include "sdvbs_common.h"
#include <enerc.h>
I2D * convertF2DtoI2D(F2D * in)
{
	I2D * out = iSetArray(in->height, in->width, 0);

	int i, j;
	for (i = 0; i < in->height; i++)
        for (j = 0; j < in->width; j++){
            APPROX float temp = subsref(in, i, j);
			subsref(out, i, j) = (int) round((ENDORSE(temp)));
        }
	return out;
}
