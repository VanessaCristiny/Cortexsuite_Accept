/********************************
Author: Sravanthi Kota Venkata
********************************/

#include <enerc.h>
#include "sdvbs_common.h"

F2D* readFile(char* fileName)
{
    accept_roi_begin();
    FILE* fp;
    F2D *fill;
    APPROX float temp;
    int rows, cols;
    int i, j;

    fp = fopen(fileName, "r");
    if(fp == NULL)
    {
        printf("Error in file %s\n", fileName);
        return NULL;
    }

    fscanf(fp, "%d", &cols);
    fscanf(fp, "%d", &rows);

    fill = fSetArray(rows, cols, 0);

    for(i=0; i<rows; i++)
    {
        for(j=0; j<cols; j++)
        {
            fscanf(fp, "%f", &(subsref(fill,i,j)) );
        }
    }

    fclose(fp);
    accept_roi_end();
    return fill;
}





