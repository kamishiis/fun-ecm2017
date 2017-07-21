#include "gmp.h"
#include "point.h"

void print_bit(unsigned long int n);
static long int count_bit(unsigned long int n);
void scalar(PROJECTIVE_POINT R, PROJECTIVE_POINT P, const unsigned long int k, const int window_size, const mpz_t N);
void E_scalar(EXTENDED_POINT R, EXTENDED_POINT P, const unsigned long int k, const int window_size, const mpz_t N);


