
#include <NTL/ZZ_p.h>
#include <NTL/ZZX.h>
#include <vector>

#include "classes.h"

using namespace std;
using namespace NTL;

Vec<ZZ_p> PolyToVec(const ZZ_pE &);

ZZ_pE VecToPoly(const Vec<ZZ_p> &);

string HashPermutation(const vector<int> &);

string HashVector(const Vec<ZZ_p> &);

void Shuffle(vector<int> &);

void Permute(Vec<ZZ_p> &, const vector<int> &, const Vec<ZZ_p> &);

bool VerifyBall(const Vec<ZZ_p> &);

void Multiply(Vec<ZZ_p> &, const ZZ_pE &, const Vec<ZZ_p> &);

void RandomVector(Vec<ZZ_p> &);

void ShortVector(Vec<ZZ_p> &);

void Expand(Vec<ZZ_p> &, const Vec<ZZ_p> &);

void SecretPolysToMat(Mat<ZZ_p> &, const Vec<CommitMessage> &, const BinaryChallenge &);

void CreateZKProofMessage(Mat<ProofMessage> &, const ZZ_pE &, const Vec<CommitMessage> &,const BinaryChallenge &);

void CreateSingleProof(ProofMessage &, const ZZ_pE &, const Vec<ZZ_p> &);

void CreateZKProof(Mat<Proof> &, Mat<ProofMessage> &, const Vec<TernaryChallenge> &);

void CreateTernaryChallenge(Vec<TernaryChallenge> &);

void TargetPolysToMat(Mat<ZZ_p>&,const ZZ_pE &,const Vec<Response>&);

void VerifyZKProof(const Mat<Proof> &, const Vec<TernaryChallenge> &, const ZZ_pE &, const Vec<Response> &);

void InitializeZKProof(Mat<ProofMessage>&,Vec<TernaryChallenge>&,Mat<Proof>&);
