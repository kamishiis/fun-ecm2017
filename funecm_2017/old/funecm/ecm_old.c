#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include "gmp.h"
#include "point.h"
#include "scalar.h"
//aaaaaaaaaaaaaaa
void ecm(mpz_t f, const mpz_t N, const mpz_t X, const mpz_t Y, mpz_t d, const unsigned long int B1, const unsigned long int B2, FILE *fp, const int window_size)
{
	PROJECTIVE_POINT P;
	PROJECTIVE_POINT MP;
	int e;
	int i;
	mpz_t tmp;
	mpz_t tmp2;
	mpz_t inv;
	
	mpz_init(tmp);
	mpz_init(tmp2);
	mpz_init(inv);

	projective_point_init(P);
	projective_point_init(MP);
		
	PROJECTIVE_POINT R, G;
	PROJECTIVE_POINT T;
	PROJECTIVE_POINT U[210];
	unsigned long int r = 210;
	unsigned long int v, v2, u, vv2;
	mpz_t d2;
	mpz_t rop;
	mpz_t gxuz;
	mpz_t gzux;

	mpz_init(d2);
	mpz_init(rop);
	mpz_init(gxuz);
	mpz_init(gzux);

	projective_point_init(R);
	projective_point_init(G);
	projective_point_init(T);
	for(i=0;i<r;i++){
	  projective_point_init(U[i]);
	 }
	
	mpz_set_ui(T->Z,1);

	/* set P */
	if (X == NULL)
		mpz_set_ui(P->X, 2);
	else
		mpz_set(P->X, X);
	mpz_set(P->Y, Y);
	mpz_set_ui(P->Z, 1);

	/* calcurate d if atkin_flag isn't set*/
	if (X == NULL) {
		mpz_init(d);
		mpz_pow_ui(tmp,P->X,2); //tmp = x^2
		mpz_mod(tmp,tmp,N);
		mpz_pow_ui(tmp2,P->Y,2); //tmp2 = y^2
		mpz_mod(tmp2,tmp2,N);
		mpz_sub(d,tmp2,tmp); //d = y^2-x^2
		mpz_sub_ui(d,d,1); //d = y^2-x^2-1
		mpz_mul_mod(tmp,tmp,tmp2,N); //tmp = x^2y^2
		mpz_invert(tmp,tmp,N);
		mpz_mul_mod(d,d,tmp,N); //dの値
	}

	/* set prime number */
	unsigned long int p = 2;
	mpz_t prime;
	mpz_init(prime);
	mpz_set_ui(prime, p);

	double stage1_time, stage2_time = -1;
	double start, end;
	start = omp_get_wtime();
	/* stage1 */
	while (p <= B1) {
		/* e = log p k */
		e = (int)(log(B1) / log(p));
		for (i = 1; i <= e; i++) {
			/* P_Z <- 1 */
			mpz_invert(inv, P->Z, N);
			mpz_mul_mod(P->X, P->X, inv, N);
			mpz_mul_mod(P->Y, P->Y, inv, N);
			mpz_set_ui(P->Z, 1);
			scalar(P, P, p, window_size, N);
			mpz_gcd(f, P->X, N);
			if (mpz_cmp_ui(f,1) != 0) {
				end = omp_get_wtime();
				stage1_time = end - start;
				//mpz_set_ui(f,1);
				goto FACTOR_FOUND;
			}
		}

		mpz_nextprime(prime, prime);
		p = mpz_get_ui(prime);
	}
	end = omp_get_wtime();
	stage1_time = end - start;

	start = omp_get_wtime();
		/* stage2 */
	
	bsgs(f,P,B1,B2,d,window_size,N,fp);
	
	/*int rr = (r+1)/2;
	for (i=0;i<rr;i++) {
	    scalar(U[i],P,i,window_size,N);
	}
	
	mpz_nextprime(prime,prime);
	p = mpz_get_ui(prime);
	v = p/r;
	v2 = v;
	scalar(R,P,r,window_size,N);
	mpz_set_ui(d2,1);
	
	while (p <= B2) {
		v = p/r;
		if(v>v2){
		  scalar(R,P,v*r,window_size,N);
		  v2 = v;
		}
		u = p%rr;
		  mpz_mul_mod(gxuz,R->Y,U[u]->Z,N);
		  mpz_mul_mod(gzux,R->Z,U[u]->Y,N);
		  mpz_sub(tmp,gxuz,gzux);
		  mpz_mul_mod(d2,d2,tmp,N);
		mpz_nextprime(prime, prime);
		p = mpz_get_ui(prime);
	}
	mpz_gcd(f,d2,N);
	*/
	end = omp_get_wtime();
	stage2_time = end - start;

FACTOR_FOUND:
	gmp_fprintf(fp,"Stage1: d = %Zd\n", d);
	fprintf(fp, "Stage1 time: %f seconds\n", stage1_time);
	if (stage2_time != -1){
		fprintf(fp, "Stage2 time: %f seconds\n", stage2_time);
		fprintf(fp, "Stage2 gcd: %ld\n", mpz_get_ui(f));
	}
	else
		fprintf(fp, "Stage2 time: ----\n");

	projective_point_clear(P);
	mpz_clear(tmp);
	mpz_clear(tmp2);
	mpz_clear(inv);
	mpz_clear(prime);
	
	mpz_clear(gxuz);
	mpz_clear(gzux);
	mpz_clear(d2);
	mpz_clear(rop);
	projective_point_clear(R);
	//	projective_point_clear(G);
	projective_point_clear(T);
	projective_point_clear(MP);
       	for(i=0;i<r;i++)
	  projective_point_clear(U[i]); 
	
}
