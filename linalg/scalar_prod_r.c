/*******************************************************************************
 * $Id$
 *
 * File scalar_prod_r.c
 *
 *   double scalar_prod_r(spinor * const S,spinor * const R, const int N)
 *     Returns the real part of the scalar product (*R,*S)
 *
 *******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#ifdef MPI
#include <mpi.h>
#endif
#include "su3.h"
#include "scalar_prod_r.h"

/*  R input, S input */
double scalar_prod_r(spinor * const S,spinor * const R, const int N){
  int ix;
  static double ks,kc,ds,tr,ts,tt;
  spinor *s,*r;
  
  ks=0.0;
  kc=0.0;
  
  for (ix=0;ix<N;ix++){
    s=(spinor *) S + ix;
    r = (spinor *) R + ix;
    
    ds=(*r).s0.c0.re*(*s).s0.c0.re + (*r).s0.c0.im*(*s).s0.c0.im + 
       (*r).s0.c1.re*(*s).s0.c1.re + (*r).s0.c1.im*(*s).s0.c1.im + 
       (*r).s0.c2.re*(*s).s0.c2.re + (*r).s0.c2.im*(*s).s0.c2.im + 
       (*r).s1.c0.re*(*s).s1.c0.re + (*r).s1.c0.im*(*s).s1.c0.im + 
       (*r).s1.c1.re*(*s).s1.c1.re + (*r).s1.c1.im*(*s).s1.c1.im + 
       (*r).s1.c2.re*(*s).s1.c2.re + (*r).s1.c2.im*(*s).s1.c2.im + 
       (*r).s2.c0.re*(*s).s2.c0.re + (*r).s2.c0.im*(*s).s2.c0.im + 
       (*r).s2.c1.re*(*s).s2.c1.re + (*r).s2.c1.im*(*s).s2.c1.im + 
       (*r).s2.c2.re*(*s).s2.c2.re + (*r).s2.c2.im*(*s).s2.c2.im + 
       (*r).s3.c0.re*(*s).s3.c0.re + (*r).s3.c0.im*(*s).s3.c0.im + 
       (*r).s3.c1.re*(*s).s3.c1.re + (*r).s3.c1.im*(*s).s3.c1.im + 
       (*r).s3.c2.re*(*s).s3.c2.re + (*r).s3.c2.im*(*s).s3.c2.im;
    
    tr = ds + kc;
    ts = tr + ks;
    tt = ts-ks;
    ks = ts;
    kc = tr-tt;
  }
  kc = ks + kc;

#if defined MPI
  
  MPI_Allreduce(&kc, &ks, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
  return ks;

#endif

  return kc;

}
