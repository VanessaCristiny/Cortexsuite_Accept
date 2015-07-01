/*
 * svdcomp - SVD decomposition routine.
 * Takes an mxn matrix a and decomposes it into udv, where u,v are
 * left and right orthogonal transformation matrices, and d is a
 * diagonal matrix of singular values.
 *
 * This routine is adapted from svdecomp.c in XLISP-STAT 2.1 which is
 * code from Numerical Recipes adapted by Luke Tierney and David Betz.
 *
 * Input to dsvd is as follows:
 *   a = mxn matrix to be decomposed, gets overwritten with u
 *   m = row dimension of a
 *   n = column dimension of a
 *   w = returns the vector of singular values of a
 *   v = returns the right orthogonal transformation matrix
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <enerc.h>
#include "common/sdvbs_common.h"
#include "defs_and_types.h"

static APPROX double PYTHAG(APPROX double a, APPROX double b)
{
    accept_roi_begin();
    APPROX double at, bt, ct, result;
    at = fabs((ENDORSE(a)));
    bt = fabs((ENDORSE(b)));

    if (ENDORSE(at) > ENDORSE(bt))       { ct = bt / at; result = at * sqrt(1.0 + ct * ct); }
    else if (ENDORSE(bt) > 0.0) { ct = at / bt; result = bt * sqrt(1.0 + ct * ct); }
    else result = 0.0;
    return(result);
    accept_roi_end();
}

#define a(i,j) subsref(input, i, j)
#define w(i) subsref(sOut, 0, i)
#define v(i, j) subsref(vOut, i, j)

int svd(F2D *input, F2D *sOut, F2D *vOut)
{
    accept_roi_begin();
    int flag, i, its, j, jj, k, l, nm;
    double c, f, h, x, y, z;
    double anorm = 0.0, g = 0.0;
    APPROX double s, scale = 0.0;
    APPROX double *rv1;

    int m = input->height;
    int n = input->width;

    if (m < n)
    {
        fprintf(stderr, "#rows must be > #cols \n");
        return(0);
    }

    rv1 = (double *)malloc((unsigned int) n*sizeof(double));

/* Householder reduction to bidiagonal form */
    for (i = 0; i < n; i++)
    {
        /* left-hand reduction */
        l = i + 1;
        rv1[i] = scale * g;
        s = scale = g = 0.0;
        if (i < m)
        {
            for (k = i; k < m; k++)
                scale += fabs((double)a(k, i));
            if (ENDORSE(scale))
            {
                for (k = i; k < m; k++)
                {
                    a(k,i) = (float)((double)a(k,i)/(ENDORSE(scale)));
                    s += ((double)a(k,i) * (double)a(k,i));
                }
                f = (double)a(i,i);
                //adding code
                double temp = ENDORSE(s);
                g = -SIGN(sqrt(temp), f);
                h = f * g - (ENDORSE(s));
                a(i,i) = (float)(f - g);
                if (i != n - 1)
                {
                    for (j = l; j < n; j++)
                    {
                        for (s = 0.0, k = i; k < m; k++)
                            s += ((double)a(k,i) * (double)a(k,j));
                        f = (ENDORSE(s)) / h;
                        for (k = i; k < m; k++)
                            a(k,j) += (float)(f * (double)a(k,i));
                    }
                }
                for (k = i; k < m; k++)
                    a(k,i) = (float)((double)(a(k,i)*(ENDORSE(scale))));
            }
        }
        w(i) = (float)(ENDORSE(scale * g));

        /* right-hand reduction */
        g = 0.0; 
        s = scale = 0.0;
        if (i < m && i != n - 1)
        {
            for (k = l; k < n; k++)
                scale += fabs((double)a(i,k));
            if (ENDORSE(scale))
            {
                for (k = l; k < n; k++)
                {
                    a(i,k) = (float)((double)(a(i,k)/(ENDORSE(scale))));
                    s += ((double)a(i,k) * (double)a(i,k));
                }
                f = (double)a(i,l);
                //adding code
                double temp = ENDORSE(s);

                g = -SIGN(sqrt(temp), f);
                h = f * g - (ENDORSE(s));
                a(i,l) = (float)(f - g);
                for (k = l; k < n; k++)
                    rv1[k] = (double)(a(i,k) / h);
                if (i != m - 1)
                {
                    for (j = l; j < m; j++)
                    {
                        for (s = 0.0, k = l; k < n; k++)
                            s += ((double)a(j,k) * (double)a(i,k));
                        for (k = l; k < n; k++)
                            a(j,k) += (float)(ENDORSE(s * rv1[k]));
                    }
                }
                for (k = l; k < n; k++)
                    a(i,k) = (float)((double)(ENDORSE(a(i,k)*scale)));
            }
        }
        float temp = ENDORSE(rv1[i]);
        anorm = MAX(anorm, (fabs((double)w(i)) + fabs(temp)));
    }

    /* accumulate the right-hand transformation */
    for (i = n - 1; i >= 0; i--)
    {
        if (i < n - 1)
        {
            if (ENDORSE(g))
            {
                for (j = l; j < n; j++)
                    v(j,i) = (float)(((double)a(i,j) / (double)( (a(i,l)) / g)));
                    /* double division to avoid underflow */
                for (j = l; j < n; j++)
                {
                    for (s = 0.0, k = l; k < n; k++)
                        s += ((double)a(i,k) * (double)v(k,j));
                    for (k = l; k < n; k++)
                        v(k,j) += (float)(ENDORSE(s * (double)v(k,i)));
                }
            }
            for (j = l; j < n; j++)
                v(i,j) = v(j,i) = 0.0;
        }
        v(i,i) = 1.0;
        g = ENDORSE(rv1[i]);
        l = i;
    }

    /* accumulate the left-hand transformation */
    for (i = n - 1; i >= 0; i--)
    {
        l = i + 1;
        g = (double)w(i);
        if (i < n - 1)
            for (j = l; j < n; j++)
                a(i,j) = 0.0;
        if (g)
        {
            g = 1.0 / g;
            if (i != n - 1)
            {
                for (j = l; j < n; j++)
                {
                    for (s = 0.0, k = l; k < m; k++)
                        s += ((double)a(k,i) * (double)a(k,j));
                    f = ((ENDORSE(s)) / (double)a(i,i)) * g;
                    for (k = i; k < m; k++)
                        a(k,j) += (float)(f * (double)a(k,i));
                }
            }
            for (j = i; j < m; j++)
                a(j,i) = (float)((double)(a(j,i)*g));
        }
        else
        {
            for (j = i; j < m; j++)
                a(j,i) = 0.0;
        }
        ++a(i,i);
    }

    /* diagonalize the bidiagonal form */
    for (k = n - 1; k >= 0; k--)
    {                             /* loop over singular values */
        for (its = 0; its < 30; its++)
        {                         /* loop over allowed iterations */
            flag = 1;
            for (l = k; l >= 0; l--)
            {                     /* test for splitting */
                nm = l - 1;
                float temp = ENDORSE(rv1[l]);
                if (fabs(temp) + anorm == anorm)
                {
                    flag = 0;
                    break;
                }
                if (fabs((double)w(nm)) + ENDORSE(anorm) == ENDORSE(anorm))
                    break;
            }
            if (flag)
            {
                c = 0.0;
                s = 1.0;
                for (i = l; i <= k; i++)
                {
                    f = (ENDORSE(s)) * ENDORSE(rv1[i]);
                    if (fabs(f) + anorm != anorm)
                    {
                        g = (double)w(i);
                        h = ENDORSE(PYTHAG(f, g));
                        w(i) = (float)h;
                        h = 1.0 / h;
                        c = g * h;
                        s = (- f * h);
                        for (j = 0; j < m; j++)
                        {
                            y = (double)a(j,nm);
                            z = (double)a(j,i);
                            a(j,nm) = (float)(ENDORSE(y * c + z * s));
                            a(j,i) = (float)(ENDORSE(z * c - y * s));
                        }
                    }
                }
            }
            z = (double)w(k);
            if (l == k)
            {                  /* convergence */
                if (z < 0.0)
                {              /* make singular value nonnegative */
                    w(k) = (float)(-z);
                    for (j = 0; j < n; j++)
                        v(j,k) = (-v(j,k));
                }
                break;
            }
            if (its >= 30) {
                free((void*) rv1);
                fprintf(stderr, "No convergence after 30,000! iterations \n");
                return(0);
            }

            /* shift from bottom 2 x 2 minor */
            x = (double)w(l);
            nm = k - 1;
            y = (double)w(nm);
            g = ENDORSE(rv1[nm]);
            h = ENDORSE(rv1[k]);
            f = ((y - z) * (y + z) + (g - h) * (g + h)) / (2.0 * h * y);
            g = ENDORSE(PYTHAG(f, 1.0));
            f = ((x - z) * (x + z) + h * ((y / (f + SIGN(g, f))) - h)) / x;

            /* next QR transformation */
            c = 1.0;
            s = 1.0;
            for (j = l; j <= nm; j++)
            {
                i = j + 1;
                g = ENDORSE(rv1[i]);
                y = (double)w(i);
                h = (ENDORSE(s)) * g;
                g = c * g;
                z = ENDORSE(PYTHAG(f, h));
                rv1[j] = z;
                c = f / z;
                s = h / z;
                f = x * c + g * (ENDORSE(s));
                g = g * c - x * (ENDORSE(s));
                h = y * (ENDORSE(s));
                y = y * c;
                for (jj = 0; jj < n; jj++)
                {
                    x = (double)v(jj,j);
                    z = (double)v(jj,i);
                    v(jj,j) = (float)(ENDORSE(x * c + z * s));
                    v(jj,i) = (float)(ENDORSE(z * c - x * s));
                }
                z = ENDORSE(PYTHAG(f, h));
                w(j) = (float)z;
                if (z)
                {
                    z = 1.0 / z;
                    c = f * z;
                    s = h * z;
                }
                f = (c * g) + ((ENDORSE(s))  * y);
                x = (c * y) - ((ENDORSE(s)) * g);
                for (jj = 0; jj < m; jj++)
                {
                    y = (double)a(jj,j);
                    z = (double)a(jj,i);
                    a(jj,j) = (float)(ENDORSE(y * c + z * s));
                    a(jj,i) = (float)(ENDORSE(z * c - y * s));
                }
            }
            rv1[l] = 0.0;
            rv1[k] = f;
            w(k) = (float)x;
        }
    }

    free((void*) rv1);
    accept_roi_end();
    return(1);
}
