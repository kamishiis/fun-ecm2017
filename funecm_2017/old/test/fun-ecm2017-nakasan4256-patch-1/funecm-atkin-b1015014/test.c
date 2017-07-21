#include <stdio.h>
#include <math.h>
#include "gmp.h"
#include "point.h"

int main(){
  mpz_t s,N,d,X,Y,f,inv;
  mpz_inits(s,N,d,X,Y,f,inv,NULL);
  mpz_set_ui(s,167441);
  mpz_set_ui(X,2);
  mpz_set_ui(Y,4);
    unsigned int i,j,k;
  i=mpz_set_str(d,"1060161481199018062",10);
  i=mpz_set_str(N,"9692904970962450851",10);

  int window_size=4;
  PROJECTIVE_POINT pP,pkP;
  projective_point_init(pP);
  projective_point_init(pkP);
  mpz_set_str(pP->X,"213511708493513968",10);
  mpz_set_str(pP->Y,"1898872073762615785",10);
  mpz_set_str(pP->Z,"3986088346883504500",10);
  EXTENDED_POINT eP,ekP;
  extended_point_init(eP);
  extended_point_init(ekP);
  protoext(eP,pP,N);
  extended_point_set(ekP,eP);


  for(i=2;i<1000;i++){
    /* P_Z <- 1 */
    mpz_invert(inv, pP->Z, N);
    mpz_mul_mod(pP->X, pP->X, inv, N);
    mpz_mul_mod(pP->Y, pP->Y, inv, N);
    mpz_set_ui(pP->Z, 1);

    scalar(pkP,pP,i,d,window_size,N);
    gmp_printf("scalar %d:(%Zd,%Zd,%Zd)\n",i,pkP->X,pkP->Y,pkP->Z);

      extended_dedicated_add(ekP,ekP,eP,N);
    gmp_printf("easy   %d:(%Zd,%Zd,%Zd)\n",i,ekP->X,ekP->Y,ekP->Z);
  }
}
