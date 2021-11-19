
#include "commitment.h"

void KeyGenCom(ComKey &comKey){
  comKey.PK = random_ZZ_pE();}

void Commit(Commitment &commitment, const ComKey &comKey, const ZZ_pE &m){
  SampleBounded(commitment.open,smallB),
  commitment.message = m, commitment.com = comKey.PK*commitment.message+commitment.open;}
