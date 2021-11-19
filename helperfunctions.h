
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pE.h>
#include "parameters.h"
#include <random>
#include <algorithm>
#include "sha2.h"

using namespace std;
using namespace NTL;

void Shuffle(ZZ_pE &);

string ZZ_pEToString(const ZZ_pE &);

void SampleBounded(ZZ_pE &, const long &);

bool isBounded(const ZZ_pE &, const double &);

Vec<ZZ_p> PolyToVec(const ZZ_pE &);

ZZ_pE VecToPoly(const Vec<ZZ_p> &);

string HashPermutation(const vector<int> &);

string HashVector(const Vec<ZZ_p> &);

void SamplePermutation(vector<int> &);

void Permute(Vec<ZZ_p> &, const vector<int> &, const Vec<ZZ_p> &);

bool VerifyBall(const Vec<ZZ_p> &);

void Multiply(Vec<ZZ_p> &, const ZZ_pE &, const Vec<ZZ_p> &);

void RandomVector(Vec<ZZ_p> &);

void ShortVector(Vec<ZZ_p> &);

void Expand(Vec<ZZ_p> &, const Vec<ZZ_p> &);
