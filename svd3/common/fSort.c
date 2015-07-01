/********************************
Author: Sravanthi Kota Venkata
********************************/

#include <enerc.h>
#include "sdvbs_common.h"

F2D* fSort(F2D* in, int dim)
{
    F2D *sorted;
    int rows, cols, i, j, k, temp;

    rows = in->height;
    cols = in->width;

    sorted = fDeepCopy(in);
    accept_roi_begin();
    for(k=0; k<cols; k++)
    {
        for(i=0; i<rows; i++)
        {
            for(j=i+1; j<rows; j++)
            {
                APPROX float sik, sjk;
                sik = subsref(sorted,i,k);
                sjk = subsref(sorted,j,k);
    
                if(ENDORSE(sik) < ENDORSE(sjk))
                {
                    temp = ENDORSE(sjk);
                    sjk = sik;
                    sik = temp;
                }
            }
        }
    }
    accept_roi_end();
    return sorted;

}




