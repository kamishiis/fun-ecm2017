#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include "point.h"

void BSGS(mpz_t p,PROJECTIVE_POINT P,const unsigned long int B1,const unsigned long int B2,mpz_t D,const int window_size,const mpz_t N,FILE *fp){

  mpz_t tB1,tB2;
  mpz_inits(tB1,tB2,NULL);
  mpz_set_ui(tB1,B1);
  mpz_set_ui(tB2,B2);
  unsigned int f=210;
  unsigned long int i,j,k;
  EXTENDED_POINT baby_step[f];
  for(i=0;i<f;i++){
    extended_point_init(baby_step[i]);
  }
  EXTENDED_POINT P0;
  extended_point_init(P0);
  protoext(P0,P,N);
  EXTENDED_POINT T;
  extended_point_init(T);
  dedicated_doubling(T,P0,N);


  mpz_t tf,ti,gcd;
  mpz_inits(tf,ti,gcd,NULL);
  mpz_set_ui(tf,f);

  gmp_fprintf(fp,"           P: ( %Zd , %Zd , %Zd )\n",P0->X,P0->Y,P0->Z);
  for(i=1;i<f;i+=2){
    mpz_set_ui(ti,i);
    mpz_gcd(gcd,tf,ti);
    if(mpz_cmp_ui(gcd,1)==0){
      extended_point_set(baby_step[i],P0);
    }
    extended_dedicated_add(P0,P0,T,N);
  }

  mpz_t ts,d;
  mpz_inits(ts,d,NULL);
  long int s,v,v2,u;
  mpz_nextprime(ts,tB1);
  s=mpz_get_ui(ts);
  v=s/f;
  v2=v;
  mpz_set_ui(d,1);
  PROJECTIVE_POINT R,G;
  projective_point_init(R);
  projective_point_init(G);
  EXTENDED_POINT eG,eR;
  extended_point_init(eG);
  extended_point_init(eR);
  scalar(R,P,f,D,window_size,N);
  scalar(G,R,v,D,window_size,N);
  protoext(eG,G,N);
  protoext(eR,R,N);
  AFFINE_POINT aG,ababy_step;
  affine_point_init(aG);
  affine_point_init(ababy_step);
  EXTENDED_POINT DD;
  extended_point_init(DD);

  mpz_t a1,a2,u1,u2;
  mpz_t A,B,inv,aGx,abx;
  mpz_inits(a1,a2,u1,u2,NULL);
  mpz_inits(A,B,inv,aGx,abx,NULL);

  while(s<=B2){
    v=s/f;
    while(v>v2){
      extended_dedicated_add(eG,eG,eR,N);
      v2++;
    }

    u=s%f;
    // gmp_fprintf(fp,"s=210v+u :\n",u1);
    exttoaff(aG,eG,N);
    exttoaff(ababy_step,baby_step[u],N);
    mpz_mul_mod(u1,eG->Y,baby_step[u]->Z,N);
    mpz_mul_mod(u2,eG->Z,baby_step[u]->Y,N);
    mpz_sub(u1,u1,u2);
    mpz_mod(u1,u1,N);
/*    mpz_add_ui(a1,aG->y,1);
    mpz_mul_si(a2,aG->y,-1);
    mpz_add_ui(a2,a2,1);
    mpz_mod(a2,a2,N);
    mpz_invert(a2,a2,N);
    mpz_mul_mod(u1,a1,a2,N);

    mpz_add_ui(a1,ababy_step->y,1);
    mpz_mul_si(a2,ababy_step->y,-1);
    mpz_add_ui(a2,a2,1);
    mpz_mod(a2,a2,N);
    mpz_invert(a2,a2,N);
    mpz_mul_mod(u2,a1,a2,N);
    mpz_sub(u1,u1,u2);

    //gmp_printf("u1=%Qd\n",u1);
    // caluculate A and B
  /*  mpz_sub_ui(a1,D,1);
    mpz_mul_ui(a1,a1,2);
    mpz_mul_si(a2,D,-1);
    mpz_sub_ui(a2,a2,1);
    mpz_invert(a2,a2,N);
    mpz_mul(A,a1,a2);
    mpz_mod(A,A,N);
    mpz_set_ui(a1,4);
    mpz_mul(B,a1,a2);
    mpz_mod(B,B,N);
    //caluculate aGx and abx
    mpz_mul_ui(inv,B,3);
    mpz_invert(inv,inv,N);
    mpz_invert(B,B,N);
    mpz_mul_mod(aGx,u1,B,N);
    mpz_mul_mod(inv,A,inv,N);
    mpz_add(aGx,aGx,inv);
    mpz_mod(aGx,aGx,N);
    mpz_mul_mod(abx,u2,B,N);

    mpz_sub(aGx,aGx,abx);
    mpz_mod(aGx,aGx,N);
    mpz_sub(u1,aGx,abx);
    */

    mpz_mul_mod(d,d,u1,N);
    mpz_nextprime(ts,ts);
    s=mpz_get_ui(ts);
  }
  gmp_printf(" d== %Zd\n",d);

  mpz_gcd(p,d,N);

  mpz_clear(tB1);
  mpz_clear(tB2);
  mpz_clear(tf);
  mpz_clear(ti);
  mpz_clear(gcd);
  mpz_clear(ts);
  mpz_clear(d);
  mpz_clear(a1);
  mpz_clear(a2);
  mpz_clear(u1);
  mpz_clear(u2);
  mpz_clear(A);
  mpz_clear(B);
  mpz_clear(inv);
  mpz_clear(aGx);
  mpz_clear(abx);
  extended_point_clear(DD);
  affine_point_clear(aG);
  affine_point_clear(ababy_step);
  for(i=0;i<f;i++){
    extended_point_clear(baby_step[i]);
  }
	extended_point_clear(P0);
  extended_point_clear(T);
  projective_point_clear(R);
  projective_point_clear(G);
  extended_point_clear(eR);
  extended_point_clear(eG);
}
