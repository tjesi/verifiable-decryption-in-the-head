
#ifndef HEADER_P
#define HEADER_P

#include <NTL/ZZ_pX.h>

// Parameters:
// Ring Rq = Z_q[X] / <X^N + 1>
// Plaintext modulus p
// Noise-bounds smallB and largeB

const long N              = 2048;
const long double q       = pow(2,53)+pow(2,36)+1;
const long p              = 2;
const long lambda         = 40;
const long tau            = 1000;
const long mu             = 1.7*lambda;
const double smallB       = 1;

#endif
