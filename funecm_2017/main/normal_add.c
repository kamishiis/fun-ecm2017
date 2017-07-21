#include <stdio.h>
#include "gmp.h"
#include "point.h"

void extended_dedicated_add(EXTENDED_POINT R, EXTENDED_POINT P, EXTENDED_POINT Q, const mpz_t N)
{
	mpz_t A,B,C,D,E,F,G,H,tmp;
	
	mpz_inits(A,B,C,D,E,F,G,H,tmp,NULL);
	
	/* A<-(Y1-X1)*(Y2+X2) */
	mpz_sub(A, P->Y, P->X);
	mpz_add(tmp, Q->Y, Q->X);
	mpz_mul_mod(A, A, tmp, N);

	/* B<-(Y1+X1)*(Y2-X2) */
	mpz_add(B, P->Y, P->X);
	mpz_sub(tmp, Q->Y, Q->X);
	mpz_mul_mod(B, B, tmp, N);

	/* C<-2*Z1*T2 */
	mpz_mul_ui(C, P->Z, 2);
	mpz_mul_mod(C, C, Q->T, N);

	/* D<-2*T1*Z2 */
	mpz_mul_ui(D, P->T, 2);
	mpz_mod(D, D, N);
	mpz_mul_mod(D, D, Q->Z, N);

	/* E<-D+C */
	mpz_add(E, D, C);
	mpz_mod(E, E, N);
	
	/* F<-B-A */
	mpz_sub(F, B, A);
	mpz_mod(F, F, N);

	/* G<-B+A */
	mpz_add(G, B, A);
	mpz_mod(G, G, N);
	
	/* H<-D-C */
	mpz_sub(H, D, C);
	mpz_mod(H, H, N);

	/* X3<-E*F */
	mpz_mul_mod(R->X, E, F, N);
	/* Y3<-G*H */
	mpz_mul_mod(R->Y, G, H, N);
	/* T3<-E*H */
	mpz_mul_mod(R->T, E, H, N);
	/* Z3<-F*G */
	mpz_mul_mod(R->Z, F, G, N);

	mpz_clears(A,B,C,D,E,F,G,H,tmp,NULL);
}

void projective_extended_add(PROJECTIVE_POINT R,PROJECTIVE_POINT P,PROJECTIVE_POINT Q,mpz_t d,const mpz_t N){
  mpz_t A,B,C,dC,D,E,F,G,H,I,J,K,L,M,O,S,T,aG;
  mpz_inits(A,B,C,dC,D,E,F,G,H,I,J,K,L,M,O,S,T,aG,NULL);

  //R-X
  // A = Z1*Z2
  mpz_mul_mod(A,P->Z,Q->Z,N);
  // B = A^2
  mpz_mul_mod(B,A,A,N);
  //C = X1*X2
  mpz_mul_mod(C,P->X,Q->X,N);
  //D = Y1*Y2
  mpz_mul_mod(D,P->Y,Q->Y,N);
  //dC = d*C
  mpz_mul_mod(dC,d,C,N);
  //E = dC*D
  mpz_mul_mod(E,dC,D,N);
  //F = B - E
  mpz_sub(F,B,E);
  //G = B + E
  mpz_add(G,B,E);
  //H = P->X + P->Y
  mpz_add(H,P->X,P->Y);
  //I = Q->X + Q->Y
  mpz_add(I,Q->X,Q->Y);
  //J = C + D
  mpz_add(J,C,D);
  //K = H * I
  mpz_mul_mod(K,H,I,N);
  //L = K - C
  mpz_sub(L,K,C);
  //M = L - D
  mpz_sub(M,L,D);
  //O = F * M
  mpz_mul_mod(O,F,M,N);
  //R->X = A * O
  mpz_mul_mod(R->X,A,O,N);
  
  //R->Y
  //aG = A * G
  mpz_mul_mod(aG,A,G,N);
  //S = D - C
  mpz_sub(S,D,C);
  //R->Y = aG * S
  mpz_mul_mod(R->Y,aG,S,N);
  
  //R->Z
  mpz_mul_mod(R->Z,F,G,N);
  mpz_clears(A,B,C,dC,D,E,F,G,H,I,J,K,L,M,O,S,T,aG,NULL);
  }
