#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include "point.h"
void BSGS2(mpz_t p,PROJECTIVE_POINT P,const unsigned long int B1,const unsigned long int B2,mpz_t D,const int window_size,const mpz_t N,FILE *fp){

  int f=210;
  int i,s,v,v2,u;
  mpz_t tB1,tB2,ts,inv,d,product,a1;
  mpz_inits(tB1,tB2,ts,inv,d,product,a1,NULL);
  mpz_set_ui(tB1,B1);
  mpz_set_ui(tB2,B2);
  mpz_nextprime(ts,tB1);
  s=mpz_get_ui(ts);

  mpz_set_ui(d,1);
  PROJECTIVE_POINT baby_step[f];
  for(i=0;i<f;i++){
    projective_point_init(baby_step[i]);
  }
  for(i=1;i<f;i++){
        scalar(baby_step[i],P,i,D,window_size,N);
  }
  PROJECTIVE_POINT giant_step;
  PROJECTIVE_POINT Giant;
  projective_point_init(giant_step);
  projective_point_init(Giant);
  v=s/f;
  v2=v;
  scalar(giant_step,P,f,D,window_size,N);
  mpz_invert(inv, giant_step->Z, N);
  mpz_mul_mod(giant_step->X, giant_step->X, inv, N);
  mpz_mul_mod(giant_step->Y, giant_step->Y, inv, N);
  mpz_set_ui(giant_step->Z, 1);

/*  mpz_invert(inv, Giant->Z, N);
  mpz_mul_mod(Giant->X, Giant->X, inv, N);
  mpz_mul_mod(Giant->Y, Giant->Y, inv, N);
  mpz_set_ui(Giant->Z, 1);
*/
  while(s<=B2){
    v=s/f;
    scalar(Giant,P,v*f,D,window_size,N);
    u=s%f;

    mpz_mul_mod(product,Giant->Y,baby_step[u]->Z,N);
    mpz_mul_mod(a1,Giant->Z,baby_step[u]->Y,N);
    mpz_sub(product,product,a1);
    mpz_mod(product,product,N);
    mpz_mul_mod(d,d,product,N);
    mpz_nextprime(ts,ts);
    s=mpz_get_ui(ts);
  }

  mpz_gcd(p,d,N);
  mpz_clears(tB1,tB2,ts,inv,d,product,a1,NULL);
  for(i=0;i<f;i++){
    projective_point_clear(baby_step[i]);
  }
  projective_point_clear(giant_step);
  projective_point_clear(Giant);
}
