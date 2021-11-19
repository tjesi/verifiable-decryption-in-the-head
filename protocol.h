
#include "encryption.h"
#include "commitment.h"
#include "classes.h"

void InitializeDecryption(EncKey &, ComKey &, Vec<CommitMessage> &, Vec<Response> &);

void Deal(CommitMessage &, const EncKey &, const ComKey &);

void Play(CommitMessage &, const int , const Statement &);

void CreateStatement(Statement &, const EncKey &);

void CreateCommitMessage(Vec<CommitMessage> &, string &, const EncKey &, const ComKey &, const Statement &);

void CreateChallenge(BinaryChallenge &);

void CreateResponseMessage(Vec<Response> &, const Vec<CommitMessage> &, const BinaryChallenge &);

void VerifyResponseMessage(const Statement &, const string , const BinaryChallenge &, const Vec<Response> &, const ZZ_pE &, const ComKey &);

string HashCommitMessage(Vec<CommitMessage> &);

bool CompareMessages(const Vec<CommitMessage> &, const Vec<CommitMessage> &);
