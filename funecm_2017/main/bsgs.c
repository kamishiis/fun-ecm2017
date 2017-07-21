#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include "point.h"

void bsgs(mpz_t p,PROJECTIVE_POINT P,const unsigned long int B1,const unsigned long int B2,const int window_size,const mpz_t N,const FILE *fp,const mpz_t D){

  unsigned long int f=210;
  unsigned long int f2 = f/2;
  unsigned long int f4 = f/4;
  unsigned long int i,s,v,v2,u;
  mpz_t tB1,ts,inv,d,product,a1,gcd,ti,tf;
  //fprintf(stdout,"%ld %ld",mpz_get_ui(eP->Y),mpz_get_ui(eP->Z));

  mpz_inits(tB1,ts,inv,d,product,a1,gcd,ti,tf,NULL);
  mpz_set_ui(tB1,B1);
  mpz_nextprime(ts,tB1);
  s=mpz_get_ui(ts);
  mpz_set_ui(d,1);
  mpz_set_ui(tf,f);
  
  EXTENDED_POINT eP;
  EXTENDED_POINT baby_step[f4];
  EXTENDED_POINT double_eP;
  EXTENDED_POINT add_eP;
  EXTENDED_POINT giant_step;
  EXTENDED_POINT Giant;
  extended_point_init(eP);
  protoext(eP,P,N);
  extended_point_init(giant_step);
  extended_point_init(Giant);
  /*for(i=0;i<f;i++){
    extended_point_init(baby_step[i]);
    if(i!=0)
      scalar2(baby_step[i],eP,i,window_size,N);
      }*/
  //fprintf(stdout,"2\n");
  extended_point_init(double_eP);
  dedicated_doubling(double_eP,eP,N);
  for(i=0;i<f4;i++){
    extended_point_init(baby_step[i]);
  }
  /*extended_point_set(baby_step[0],eP);
  for(i=1;i<f2;i++){
    //scalar2(baby_step[i],eP,(2*i+1),window_size,N);
      extended_dedicated_add(baby_step[i],d,baby_step[i-1],N);
      }*/
  extended_point_init(add_eP);
  extended_point_set(add_eP,eP);
  for(i=0;i<f4;i++){
    mpz_set_ui(ti,2*i+1);
    mpz_gcd(gcd,ti,tf);
    if(mpz_cmp_ui(gcd,1)==0){
      extended_point_set(baby_step[i],add_eP);
      }
    //extended_point_set(baby_step[i],eP);
    extended_dedicated_add(add_eP,add_eP,double_eP,N);
  }
    
  //fprintf(stdout,"3\n");
  //  projective_point_init(baby_step[0]);
  // projective_point_set(baby_step[0],P);
  
  v2=(s-f/2)/f;
  //v2=s/f;

  
  scalar2(giant_step,eP,f,window_size,N);
  scalar2(Giant,giant_step,v2,window_size,N);
  //extended_point_set(Giant,giant_step);
  /* extended_point_init(Giant,eP);
     extended_point_init(giant_step,eP);*/
  //fprintf(stdout,"4\n");

  while(s<=B2){
    v=(s-f/2)/f;
    //v=s/f;
     while(v!=v2){
      v2++;
      extended_dedicated_add(Giant,Giant,giant_step,N);
      //fprintf(stdout,"6\n");
    }
     /*if(v>v2){
      scalar2(Giant,eP,f*v,window_size,N);
      v2 = v;
      }*/
    //fprintf(stdout,"1\n");
    //fprintf(stdout,"%ld %ld",mpz_get_ui(Giant->Y),mpz_get_ui(Giant->Z));
     u=abs((s-f/2)%f-f/2);
    //u=s%f;
     mpz_mul_mod(product,Giant->Y,baby_step[(u-1)/2]->Z,N);
     mpz_mul_mod(a1,Giant->Z,baby_step[(u-1)/2]->Y,N);
     mpz_sub(product,product,a1);
     mpz_mul_mod(d,d,product,N);
     mpz_nextprime(ts,ts);
     s=mpz_get_ui(ts);
  }

  mpz_gcd(p,d,N);
  //fprintf(stdout,"d:%ld p:%Zd",mpz_get_ui(d),p);
  mpz_clears(tB1,ts,inv,d,product,a1,gcd,ti,tf,NULL);
  extended_point_clear(eP);
  for(i=0;i<f4;i++){
    extended_point_clear(baby_step[i]);
  }
  extended_point_clear(giant_step);
  extended_point_clear(Giant);
  extended_point_clear(double_eP);
  //fprintf(stdout,"5\n");
}
