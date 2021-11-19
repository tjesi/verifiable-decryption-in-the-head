
#include "zeroknowledge.h"
#include "sha2.h"

void CreateSingleProof(ProofMessage &proofMessage, const ZZ_pE &a, const Vec<ZZ_p> &secret){
  Vec<ZZ_p> expandedSecret, randomness, randomProduct;
  Vec<ZZ_p> permutedSecret, permutedSum, permutedRandomness;

  vector<int> perm(6*N);expandedSecret.SetLength(6*N);
  randomness.SetLength(6*N);randomProduct.SetLength(2*N);
  permutedSecret.SetLength(6*N);permutedSum.SetLength(6*N);
  permutedRandomness.SetLength(6*N);Expand(expandedSecret, secret);

  RandomVector(randomness);SamplePermutation(perm);
  Multiply(randomProduct, a, randomness);
  Permute(permutedRandomness, perm, randomness);
  Permute(permutedSum, perm, expandedSecret+randomness);
  Permute(permutedSecret, perm, expandedSecret);

  proofMessage.s = permutedSecret;
  proofMessage.t = permutedRandomness;
  proofMessage.u = expandedSecret+randomness;
  proofMessage.v = randomness;
  proofMessage.phi = perm;

  proofMessage.c1 = sha256(HashPermutation(perm)+HashVector(randomProduct));
  proofMessage.c2 = HashVector(permutedRandomness);
  proofMessage.c3 = HashVector(permutedSum);
}

void SecretPolysToMat(Mat<ZZ_p> &secret, const Vec<CommitMessage> &comMsg, const BinaryChallenge &binaryChlg){
  for (int j=0; j < lambda; j++){
    Vec<ZZ_p> firstHalfSecret = PolyToVec(comMsg[j].secretShare[0]+comMsg[j].secretShare[1]);
    Vec<ZZ_p> secondHalfSecret = PolyToVec(comMsg[j].secretCom[1-binaryChlg.beta[j]].open);
    Vec<ZZ_p> firstHalfError = PolyToVec(comMsg[j].errorShare[0]+comMsg[j].errorShare[1]);
    Vec<ZZ_p> secondHalfError = PolyToVec(comMsg[j].errorCom[1-binaryChlg.beta[j]].open);
    for (int i=0; i < N; i++){
      secret[j][i] = firstHalfSecret[i];
      secret[j][i+N] = secondHalfSecret[i];
      secret[j+lambda][i] = firstHalfError[i];
      secret[j+lambda][i+N] = secondHalfError[i];}}}

void CreateZKProofMessage(Mat<ProofMessage> &proofMessage, const ZZ_pE &a, const Vec<CommitMessage> &comMsg, const BinaryChallenge &binaryChlg){
  Mat<ZZ_p> secret; secret.SetDims(2*lambda,2*N);
  SecretPolysToMat(secret,comMsg,binaryChlg);
  for (int j=0; j < 2*lambda; j++){
    for (int i=0; i < mu; i++){
      CreateSingleProof(proofMessage[j][i],a, secret[j]);}}}

void CreateTernaryChallenge(Vec<TernaryChallenge> &chlg){
  for (int j=0; j < 2*lambda; j++){
    for (int i=0; i < mu; i++){
      chlg[j].beta[i] = RandomBnd(3)+1;}}}

void CreateZKProof(Mat<Proof> &zkProof, Mat<ProofMessage> &proofMessage, const Vec<TernaryChallenge> &chlg){
  for (int j=0; j < 2*lambda; j++){
    for (int i=0; i < mu; i++){
      if (chlg[j].beta[i] == 1){
        zkProof[j][i].vector1 = proofMessage[j][i].s;
        zkProof[j][i].vector2 = proofMessage[j][i].t;
      } else if (chlg[j].beta[i] == 2) {
        zkProof[j][i].vector1 = proofMessage[j][i].u;
        zkProof[j][i].perm = proofMessage[j][i].phi;
      } else if (chlg[j].beta[i] == 3) {
        zkProof[j][i].vector1 = proofMessage[j][i].v;
        zkProof[j][i].perm = proofMessage[j][i].phi;}
      zkProof[j][i].c1 = proofMessage[j][i].c1;
      zkProof[j][i].c2 = proofMessage[j][i].c2;
      zkProof[j][i].c3 = proofMessage[j][i].c3;}}}

void TargetPolysToMat(Mat<ZZ_p> &target, const ZZ_pE &a, const Vec<Response> &resp){
  for (int j=0; j < lambda; j++){
    Vec<ZZ_p> secretVec = PolyToVec(resp[j].secretCom+a*resp[j].secretShare);
    Vec<ZZ_p> errorVec = PolyToVec(resp[j].errorCom+a*resp[j].errorShare);
    for (int i=0; i < N; i++){
      target[j][i] = secretVec[i];
      target[j+lambda][i] = errorVec[i];}}}

void VerifyZKProof(const Mat<Proof> &zkProof, const Vec<TernaryChallenge> &chlg, const ZZ_pE &a, const Vec<Response> &resp){
  Mat<ZZ_p> target;target.SetDims(2*lambda,N);
  TargetPolysToMat(target,a,resp);
  bool accept = true;
  for (int j=0; j < 2*lambda; j++){
    for (int i=0; i < mu; i++){
      if (chlg[j].beta[i] == 1){
        if (zkProof[j][i].c2 != HashVector(zkProof[j][i].vector2) or zkProof[j][i].c3 != HashVector(zkProof[j][i].vector1+zkProof[j][i].vector2) or !VerifyBall(zkProof[j][i].vector1)){accept = false;}}

      else if (chlg[j].beta[i] == 2) {
        Vec<ZZ_p> prod, permuted;
        prod.SetLength(N);permuted.SetLength(6*N);
        Multiply(prod, a, zkProof[j][i].vector1);
        Permute(permuted, zkProof[j][i].perm, zkProof[j][i].vector1);
        if (zkProof[j][i].c1 != sha256(HashPermutation(zkProof[j][i].perm)+HashVector(prod-target[j]))
        or zkProof[j][i].c3 != HashVector(permuted)){accept = false;}}

      else if (chlg[j].beta[i] == 3) {
        Vec<ZZ_p> prod, permuted;
        prod.SetLength(N);permuted.SetLength(6*N);
        Multiply(prod, a, zkProof[j][i].vector1);
        Permute(permuted, zkProof[j][i].perm, zkProof[j][i].vector1);
        if (zkProof[j][i].c1 != sha256(HashPermutation(zkProof[j][i].perm)+HashVector(prod))
        or zkProof[j][i].c2 != HashVector(permuted)){
          accept = false;}
  }}}
  if (accept){
    cout << "Accept ZKP" << "\n\n";
  } else {
    cout << "Reject ZKP" << "\n\n";}}

void InitializeZKProof(Mat<ProofMessage> &proofMessage, Vec<TernaryChallenge> &ternaryChlg, Mat<Proof> &zkProof){
  proofMessage.SetDims(2*lambda,mu);
  ternaryChlg.SetLength(2*lambda);
  zkProof.SetDims(2*lambda,mu);}
