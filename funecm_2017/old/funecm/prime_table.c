#include "prime_table.h"

void make_prime_table(int D,int B1,int B2){
	int i,j;

	mpz_t tmp,tmp2;
	mpz_inits(tmp,tmp2,NULL);
	mpz_set_ui(tmp,B1);
	mpz_nextprime(tmp,tmp);
	int s=mpz_getui(tmp);
	int Js[D/2];
	int GCD_table[D/2];
	i=1;
	for(j=1;j<D/2;j++){
		mpz_gcd(tmp,j,D);
		if(mpz_cmp_ui(tmp,1)==0){
			GCD_table[j]=1;
			Js[i]=j;
			i++;
		}
	}
	for(j=i;j<D/2;j++){
		Js[j]=1;
	}

	int Mmin=(B1+D/2+1)/D;
	int Mmax=(B1+D/2-1)/D;
	int prime_table[Mmax][D/2];
	int m;
	for(m=Mmin;m<Mmax;m++){
		for(j=1;j<D/2;j++){
			if(B1<m*D+j){
				prime_table[m][j]=mpz_probab_prime_p(m*D+j,25)+mpz_probab_prime_p(m*D-j,25);
			}
		}
	}


	for(m=0;m<Mmax;m++){
		for(j=0;j<D/2;j++){
			printf("m:%d\tj:%d\tm*D+j:%d\tprime_table[m][j]:%d\n",m,j,m*D+j,prime_table[m][j]);
	}
	mpz_clear(tmp):
	mpz_clear(tmp2);
}


