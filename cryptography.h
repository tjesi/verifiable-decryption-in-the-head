
#include "classes.h"

void Shuffle(ZZ_pE &);

string ZZ_pEToString(const ZZ_pE &);

string HashCommitMessage(Vec<CommitMessage> &);

bool CompareMessages(const Vec<CommitMessage> &, const Vec<CommitMessage> &);

void SampleBounded(ZZ_pE &, const long &);

void SampleMessage(ZZ_pE &);

bool isBounded(const ZZ_pE &, const double &);

void KeyGenEnc(EncKey &);

void KeyGenCom(ComKey &);

void Encrypt(Ciphertext &, const EncKey &, const ZZ_pE &);

void RoundModP(ZZ_pE &);

void Decrypt(ZZ_pE &, const EncKey &, const Ciphertext &);

void Commit(Commitment &, const ComKey &, const ZZ_pE &);

void CorrectOpen(bool &, const ZZ_pE &,const ZZ_pE &,const ZZ_pE &);
