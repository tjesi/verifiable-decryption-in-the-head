
#include <NTL/ZZ_pX.h>

// Parameters:
// Ring Rq = Z_q[X] / <X^N + 1>
// Plaintext modulus p
// Noise-bounds smallB and largeB

const long N              = 2048;
const long double q       = pow(2,55) + pow(2,13) + 1;
const long p              = 3;
const long lambda         = 20;
const long tau            = 100;
const long mu             = 1.7*lambda;
const double smallB       = 1;
const long double largeB  = pow(2,51);
const long rounds         = 100;
