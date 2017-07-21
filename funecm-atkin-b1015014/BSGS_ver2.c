<<<<<<< HEAD
#include <stdio.h>
#include "gmp.h"
#include "point.h"

void BSGS_ver2(mpz_t p,PROJECTIVE_POINT Q0, mpz_t d,const unsigned long int B1, const unsigned long int B2,const int window_size,const mpz_t N){
  /* p=f*v+u (-d/2<=u<=d/2)*/

  unsigned long int f=210;
  int GCD_table[f/4];//{1,0,0,0,0,1,1,0,1,1,,,}
  int Js[f/4];//{11,13,17,19,,,}
  int count_gcd;
  int Mmin=(B1+f/2+1)/f;
  int Mmax=(B2+f/2-1)/f;
  int Prime_table[Mmax+1][f/2];
  int i,m;

  mpz_t gcd,t,D;
  mpz_set_ui(D,f);
  for(i=1;i<=f/2;i+=2){
    mpz_set_ui(t,i);
    mpz_gcd(gcd,D,t);
    if(mpz_cmp_ui(gcd,1)==0){
      GCD_table[(i-1)/2]=1;
      Js[count_gcd]=i;
      count_gcd++;
    }
  }

  mpz_t hoge1,hoge2,hoge3;
  for(m=Mmin;m<=Mmax;m++){
    for(i=1;i<=f/2;i+=2){
      if(B1<(m*f+i)&&(m*f-i)<B2){
        mpz_set_ui(hoge1,m);
        mpz_mul(hoge1,hoge1,D);
        mpz_add_ui(hoge2,hoge1,i);
        mpz_sub_ui(hoge3,hoge1,i);
        Prime_table[m][i-1]=mpz_probab_prime_p(hoge2,25)+mpz_probab_prime_p(hoge3,25);
      }
    }
  }

  EXTENDED_POINT tQ0;
  extended_point_init(tQ0);
  protoext(tQ0,Q0,N);
  EXTENDED_POINT Q;
  extended_point_init(Q);
  extended_point_set(Q,tQ0);
  EXTENDED_POINT T;//T=2*Q0
  extended_point_init(T);
  dedicated_doubling(T,tQ0,N);

  EXTENDED_POINT eU[f/4];//{}
  for(i=0;i<f/4;i++){
    extended_point_init(eU[i]);
  }

  for(i=0;i<f/4;i++){
    if(GCD_table[i]>0){
      extended_point_set(eU[i],Q);
    }
    extended_dedicated_add(Q,Q,T,N);
  }
  PROJECTIVE_POINT U[f/4];
  for(i=0;i<f/4;i++){
    exttopro(U[i],eU[i],N);
  }
  PROJECTIVE_POINT V;//V=f*Q0
  projective_point_init(V);
  PROJECTIVE_POINT W;//W=Mmin*V
  projective_point_init(W);
  scalar(V,Q0,f,d,window_size,N);
  scalar(W,V,Mmin,d,window_size,N);
  EXTENDED_POINT eV;
  extended_point_init(eV);
  protoext(eV,V,N);
  EXTENDED_POINT eW;
  extended_point_init(eW);
  protoext(eW,W,N);

  mpz_t a,G,Ga,Gb;
  mpz_inits(a,G,Ga,Gb);
  mpz_set_ui(a,1);
  for(m=Mmin;m<=Mmax;m++){
    for(i=0;i<count_gcd;i++){
      if(Prime_table[m][Js[i]]>0){
        mpz_mul(Ga,eW->X,U[Js[i]]->Z);
        mpz_mul(Gb,eW->Z,U[Js[i]]->X);
        mpz_sub(G,Ga,Gb);
        mpz_mul(a,a,G);
      }
    }
    extended_dedicated_add(eW,eW,eV,N);
  }
  mpz_gcd(p,a,N);
}
=======
#include <stdio.h>
#include "gmp.h"
#include "point.h"

void BSGS_ver2(mpz_t p,PROJECTIVE_POINT Q0, mpz_t d,const unsigned long int B1, const unsigned long int B2,const int window_size,const mpz_t N){
  /* p=f*v+u (-d/2<=u<=d/2)*/

  unsigned long int f=210;
  int GCD_table[f/4];//{1,0,0,0,0,1,1,0,1,1,,,}
  int Js[f/4];//{11,13,17,19,,,}
  int count_gcd;
  int Mmin=(B1+f/2+1)/f;
  int Mmax=(B2+f/2-1)/f;
  int Prime_table[Mmax+1][f/2];
  int i,m;

  mpz_t gcd,t,D;
  mpz_set_ui(D,f);
  for(i=1;i<=f/2;i+=2){
    mpz_set_ui(t,i);
    mpz_gcd(gcd,D,t);
    if(mpz_cmp_ui(gcd,1)==0){
      GCD_table[(i-1)/2]=1;
      Js[count_gcd]=i;
      count_gcd++;
    }
  }

  mpz_t hoge1,hoge2,hoge3;
  for(m=Mmin;m<=Mmax;m++){
    for(i=1;i<=f/2;i+=2){
      if(B1<(m*f+i)&&(m*f-i)<B2){
        mpz_set_ui(hoge1,m);
        mpz_mul(hoge1,hoge1,D);
        mpz_add_ui(hoge2,hoge1,i);
        mpz_sub_ui(hoge3,hoge1,i);
        Prime_table[m][i-1]=mpz_probab_prime_p(hoge2,25)+mpz_probab_prime_p(hoge3,25);
      }
    }
  }

  EXTENDED_POINT tQ0;
  extended_point_init(tQ0);
  protoext(tQ0,Q0,N);
  EXTENDED_POINT Q;
  extended_point_init(Q);
  extended_point_set(Q,tQ0);
  EXTENDED_POINT T;//T=2*Q0
  extended_point_init(T);
  dedicated_doubling(T,tQ0,N);

  EXTENDED_POINT eU[f/4];//{}
  for(i=0;i<f/4;i++){
    extended_point_init(eU[i]);
  }

  for(i=0;i<f/4;i++){
    if(GCD_table[i]>0){
      extended_point_set(eU[i],Q);
    }
    extended_dedicated_add(Q,Q,T,N);
  }
  PROJECTIVE_POINT U[f/4];
  for(i=0;i<f/4;i++){
    exttopro(U[i],eU[i],N);
  }
  PROJECTIVE_POINT V;//V=f*Q0
  projective_point_init(V);
  PROJECTIVE_POINT W;//W=Mmin*V
  projective_point_init(W);
  scalar(V,Q0,f,d,window_size,N);
  scalar(W,V,Mmin,d,window_size,N);
  EXTENDED_POINT eV;
  extended_point_init(eV);
  protoext(eV,V,N);
  EXTENDED_POINT eW;
  extended_point_init(eW);
  protoext(eW,W,N);

  mpz_t a,G,Ga,Gb;
  mpz_inits(a,G,Ga,Gb);
  mpz_set_ui(a,1);
  for(m=Mmin;m<=Mmax;m++){
    for(i=0;i<count_gcd;i++){
      if(Prime_table[m][Js[i]]>0){
        mpz_mul(Ga,eW->X,U[Js[i]]->Z);
        mpz_mul(Gb,eW->Z,U[Js[i]]->X);
        mpz_sub(G,Ga,Gb);
        mpz_mul(a,a,G);
      }
    }
    extended_dedicated_add(eW,eW,eV,N);
  }
  mpz_gcd(p,a,N);
}
>>>>>>> 408226eb93dcbd3a4de5b7a84756ff4fadfb9d48
