
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pE.h>

using namespace std;
using namespace NTL;

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
