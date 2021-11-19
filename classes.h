
#ifndef HEADER_H
#define HEADER_H

#include <NTL/ZZ_p.h>
#include <NTL/ZZX.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_pE.h>
#include "parameters.h"
#include "commitment.h"
#include "encryption.h"
#include <vector>

using namespace NTL;
using namespace std;

class DecryptionShares {
public:
  Vec<ZZ_pE> m;
  DecryptionShares(){
    m.SetLength(2);
  }
};

class Statement {
public:
  Vec<ZZ_pE> messages;
  Vec<Ciphertext> ciphertexts;

  Statement(){
    messages.SetLength(tau);
    ciphertexts.SetLength(tau);
  }
};

class CommitMessage{
public:
  Vec<ZZ_pE> secretShare, errorShare, pubKeyShare;
  Vec<Commitment> secretCom, errorCom;
  Vec<DecryptionShares> partialDecryptions;

  CommitMessage(){
    secretShare.SetLength(2);
    errorShare.SetLength(2);
    pubKeyShare.SetLength(2);
    secretCom.SetLength(2);
    errorCom.SetLength(2);
    partialDecryptions.SetLength(tau);
  }
};

class BinaryChallenge {
public:
  Vec<bool> beta;

  BinaryChallenge(){
    beta.SetLength(lambda);
  }
};

class TernaryChallenge {
public:
  Vec<long> beta;

  TernaryChallenge(){
    beta.SetLength(mu);
  }
};

class Response {
public:
  ZZ_pE secretShare, errorShare, pubKeyShare;
  ZZ_pE secretCom, errorCom, secretOpen, errorOpen;
  Vec<ZZ_pE> partialDecryption;

  Response(){
    partialDecryption.SetLength(tau);
  }
};

class ProofMessage {
public:
  Vec<ZZ_p> s,t,u,v;
  vector<int> phi;
  string c1,c2,c3;

  ProofMessage(){
    s.SetLength(6*N);
    t.SetLength(6*N);
    u.SetLength(6*N);
    v.SetLength(6*N);
    vector<int> phi(6*N);
  }
};

class Proof {
public:
  Vec<ZZ_p> vector1, vector2;
  vector<int> perm;
  string c1,c2,c3;

  Proof(){
    vector1.SetLength(6*N);
    vector2.SetLength(6*N);
    vector<int> perm(6*N);
  }
};

#endif
