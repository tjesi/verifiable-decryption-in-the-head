
#ifndef COM
#define COM

#include <NTL/ZZ_pE.h>
#include "parameters.h"
#include "helperfunctions.h"

using namespace NTL;

class ComKey {
public:
  ZZ_pE PK;
};

class Commitment {
public:
  ZZ_pE com,open,message;
};

void KeyGenCom(ComKey &);

void Commit(Commitment &, const ComKey &, const ZZ_pE &);

#endif
