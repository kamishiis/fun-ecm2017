<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include "point.h"
void BSGS2(mpz_t p,PROJECTIVE_POINT P,const unsigned long int B1,const unsigned long int B2,mpz_t D,const int window_size,const mpz_t N,FILE *fp){

  int f=2310;
  int i,s,v,v2,u;
  mpz_t ti,tf,gcd,tB1,tB2,ts,inv,d,product,a1;
  mpz_inits(ti,tf,gcd,tB1,tB2,ts,inv,d,product,a1,NULL);
  mpz_set_ui(tf,f);
  mpz_set_ui(tB1,B1);
  mpz_set_ui(tB2,B2);
  mpz_nextprime(ts,tB1);
  s=mpz_get_ui(ts);

  mpz_set_ui(d,1);
  EXTENDED_POINT baby_step[f/2];//[0]->P,[1]->3P,[2]->5P..
  EXTENDED_POINT eP;
  EXTENDED_POINT double_P;
  extended_point_init(eP);
  extended_point_init(double_P);
  protoext(eP,P,N);
  dedicated_doubling(double_P,eP,N);
  for(i=0;i<f/2;i++){
    extended_point_init(baby_step[i]);
    mpz_set_ui(ti,2*i+1);
    mpz_gcd(gcd,ti,tf);
    if(mpz_cmp_ui(gcd,1)==0){
      extended_point_set(baby_step[i],eP);
    }
    extended_dedicated_add(eP,eP,double_P,N);
  }
  PROJECTIVE_POINT giant_step;
  PROJECTIVE_POINT Giant;
  projective_point_init(giant_step);
  projective_point_init(Giant);
  EXTENDED_POINT ext_giant_step;
  EXTENDED_POINT ext_Giant;
  extended_point_init(ext_giant_step);
  extended_point_init(ext_Giant);
  v2=s/f;
  scalar(giant_step,P,f,D,window_size,N);
  scalar(Giant,giant_step,v2,D,window_size,N);
  protoext(ext_giant_step,giant_step,N);
  protoext(ext_Giant,Giant,N);

/*  mpz_invert(inv, Giant->Z, N);
  mpz_mul_mod(Giant->X, Giant->X, inv, N);
  mpz_mul_mod(Giant->Y, Giant->Y, inv, N);
  mpz_set_ui(Giant->Z, 1);
*/
  while(s<=B2){
    v=s/f;
    while(v!=v2){
      extended_dedicated_add(ext_Giant,ext_Giant,ext_giant_step,N);
      v2++;
    }
    u=s%f;

    mpz_mul_mod(product,ext_Giant->Y,baby_step[(u-1)/2]->Z,N);
    mpz_mul_mod(a1,ext_Giant->Z,baby_step[(u-1)/2]->Y,N);
    mpz_sub(product,product,a1);
    mpz_mod(product,product,N);
    mpz_mul_mod(d,d,product,N);
    mpz_nextprime(ts,ts);
    s=mpz_get_ui(ts);
  }

  mpz_gcd(p,d,N);
  mpz_clears(ti,tf,gcd,tB1,tB2,ts,inv,d,product,a1,NULL);
  for(i=0;i<f/2;i++){
    extended_point_clear(baby_step[i]);
  }
  extended_point_clear(eP);
  extended_point_clear(double_P);
  projective_point_clear(giant_step);
  projective_point_clear(Giant);
  extended_point_clear(ext_giant_step);
  extended_point_clear(ext_Giant);
}
=======
#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include "point.h"
void BSGS2(mpz_t p,PROJECTIVE_POINT P,const unsigned long int B1,const unsigned long int B2,mpz_t D,const int window_size,const mpz_t N,FILE *fp){

  int f=2310;
  int i,s,v,v2,u;
  mpz_t ti,tf,gcd,tB1,tB2,ts,inv,d,product,a1;
  mpz_inits(ti,tf,gcd,tB1,tB2,ts,inv,d,product,a1,NULL);
  mpz_set_ui(tf,f);
  mpz_set_ui(tB1,B1);
  mpz_set_ui(tB2,B2);
  mpz_nextprime(ts,tB1);
  s=mpz_get_ui(ts);

  mpz_set_ui(d,1);
  EXTENDED_POINT baby_step[f/2];//[0]->P,[1]->3P,[2]->5P..
  EXTENDED_POINT eP;
  EXTENDED_POINT double_P;
  extended_point_init(eP);
  extended_point_init(double_P);
  protoext(eP,P,N);
  dedicated_doubling(double_P,eP,N);
  for(i=0;i<f/2;i++){
    extended_point_init(baby_step[i]);
    mpz_set_ui(ti,2*i+1);
    mpz_gcd(gcd,ti,tf);
    if(mpz_cmp_ui(gcd,1)==0){
      extended_point_set(baby_step[i],eP);
    }
    extended_dedicated_add(eP,eP,double_P,N);
  }
  PROJECTIVE_POINT giant_step;
  PROJECTIVE_POINT Giant;
  projective_point_init(giant_step);
  projective_point_init(Giant);
  EXTENDED_POINT ext_giant_step;
  EXTENDED_POINT ext_Giant;
  extended_point_init(ext_giant_step);
  extended_point_init(ext_Giant);
  v2=s/f;
  scalar(giant_step,P,f,D,window_size,N);
  scalar(Giant,giant_step,v2,D,window_size,N);
  protoext(ext_giant_step,giant_step,N);
  protoext(ext_Giant,Giant,N);

/*  mpz_invert(inv, Giant->Z, N);
  mpz_mul_mod(Giant->X, Giant->X, inv, N);
  mpz_mul_mod(Giant->Y, Giant->Y, inv, N);
  mpz_set_ui(Giant->Z, 1);
*/
  while(s<=B2){
    v=s/f;
    while(v!=v2){
      extended_dedicated_add(ext_Giant,ext_Giant,ext_giant_step,N);
      v2++;
    }
    u=s%f;

    mpz_mul_mod(product,ext_Giant->Y,baby_step[(u-1)/2]->Z,N);
    mpz_mul_mod(a1,ext_Giant->Z,baby_step[(u-1)/2]->Y,N);
    mpz_sub(product,product,a1);
    mpz_mod(product,product,N);
    mpz_mul_mod(d,d,product,N);
    mpz_nextprime(ts,ts);
    s=mpz_get_ui(ts);
  }

  mpz_gcd(p,d,N);
  mpz_clears(ti,tf,gcd,tB1,tB2,ts,inv,d,product,a1,NULL);
  for(i=0;i<f/2;i++){
    extended_point_clear(baby_step[i]);
  }
  extended_point_clear(eP);
  extended_point_clear(double_P);
  projective_point_clear(giant_step);
  projective_point_clear(Giant);
  extended_point_clear(ext_giant_step);
  extended_point_clear(ext_Giant);
}
>>>>>>> 408226eb93dcbd3a4de5b7a84756ff4fadfb9d48
