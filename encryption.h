
#ifndef ENC
#define ENC

#include <NTL/ZZ_pE.h>
#include "parameters.h"
#include "helperfunctions.h"

using namespace NTL;

class Ciphertext {
public:
  ZZ_pE CTXu,CTXv;
};

class EncKey {
public:
  ZZ_pE PKa,PKb,SKs,SKe;
};

void SampleMessage(ZZ_pE &);

void KeyGenEnc(EncKey &);

void Encrypt(Ciphertext &, const EncKey &, const ZZ_pE &);

void RoundModP(ZZ_pE &);

void Decrypt(ZZ_pE &, const EncKey &, const Ciphertext &);

#endif
