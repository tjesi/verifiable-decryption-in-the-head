
#include "protocol.h"

void InitializeDecryption(EncKey &encKey, ComKey &comKey, Vec<CommitMessage> &msg, Vec<Response> &resp){
  ZZ_p::init(ZZ(q));
  ZZ_pE::init(ZZ_pX(INIT_MONO, N)+1);
  KeyGenEnc(encKey);
  KeyGenCom(comKey);
  msg.SetLength(lambda);
  resp.SetLength(lambda);}

void Deal(CommitMessage &msg, const EncKey &encKey, const ComKey &comKey){
  msg.secretShare[0] = random_ZZ_pE();
  msg.secretShare[1] = encKey.SKs - msg.secretShare[0];
  msg.errorShare[0] = random_ZZ_pE();
  msg.errorShare[1] = encKey.SKe - msg.errorShare[0];

  Commit(msg.secretCom[0],comKey,msg.secretShare[0]);
  Commit(msg.secretCom[1],comKey,msg.secretShare[1]);
  Commit(msg.errorCom[0],comKey,msg.errorShare[0]);
  Commit(msg.errorCom[1],comKey,msg.errorShare[1]);

  msg.pubKeyShare[0]
    = encKey.PKa*msg.secretShare[0] + ZZ_pE(p)*msg.errorShare[0];
  msg.pubKeyShare[1] = encKey.PKb - msg.pubKeyShare[0];}

void Play(CommitMessage &msg, const int index, const Statement &stmt){
  for (int j = 0; j < tau; j++){
    msg.partialDecryptions[j].m[index] = msg.secretShare[index]*stmt.ciphertexts[j].CTXu;
    RoundModP(msg.partialDecryptions[j].m[index]);}}

void CreateStatement(Statement &stmt, const EncKey &encKey){
  ZZ_pE m; Ciphertext ctx;
  for (int j = 0; j < tau; j++){
    SampleMessage(m); Encrypt(ctx,encKey,m);
    stmt.messages[j] = m; stmt.ciphertexts[j] = ctx;}}

void CreateCommitMessage(Vec<CommitMessage> &msg, string &hash, const EncKey &encKey, const ComKey &comKey, const Statement &stmt){
  for (int i = 0; i < lambda; i++){
    Deal(msg[i],encKey,comKey);
    Play(msg[i],0,stmt);
    Play(msg[i],1,stmt);
  } hash = HashCommitMessage(msg);}

void CreateChallenge(BinaryChallenge &chlg){
  for (int i = 0; i < lambda; i++){
    chlg.beta[i] = RandomBnd(2);}}

void CreateResponseMessage(Vec<Response> &resp, const Vec<CommitMessage> &msg, const BinaryChallenge &chlg){
  for (int i = 0; i < lambda; i++){
    int index = chlg.beta[i];
    resp[i].secretShare = msg[i].secretShare[index];
    resp[i].errorShare = msg[i].errorShare[index];
    resp[i].secretOpen = msg[i].secretCom[index].open;
    resp[i].errorOpen = msg[i].errorCom[index].open;
    resp[i].secretCom = msg[i].secretCom[1-index].com;
    resp[i].errorCom = msg[i].errorCom[1-index].com;
    resp[i].pubKeyShare = msg[i].pubKeyShare[1-index];
    for (int j = 0; j < tau; j++){
      resp[i].partialDecryption[j] = msg[i].partialDecryptions[j].m[1-index];}}}

void VerifyResponseMessage(const Statement &stmt, const string hash,
  const BinaryChallenge &chlg, const Vec<Response> &resp,
  const ZZ_pE &encKeyPK, const ComKey &comKey){
  Vec<CommitMessage> msg; msg.SetLength(lambda);
  bool shortness = true; bool correctness = true;
  for (int i = 0; i < lambda; i++){
    int index = chlg.beta[i];
    msg[i].secretCom[index].com
      = comKey.PK*resp[i].secretShare+resp[i].secretOpen;
    msg[i].errorCom[index].com
      = comKey.PK*resp[i].errorShare+resp[i].errorOpen;
    shortness = shortness and
              isBounded(resp[i].secretOpen,smallB) and
              isBounded(resp[i].errorOpen,smallB);
    msg[i].secretCom[1-index].com = resp[i].secretCom;
    msg[i].errorCom[1-index].com  = resp[i].errorCom;
    msg[i].pubKeyShare[index]
      = encKeyPK*resp[i].secretShare+ZZ_pE(p)*resp[i].errorShare;
    msg[i].pubKeyShare[1-index]
      = resp[i].pubKeyShare;
    for (int j = 0; j < tau; j++){
      msg[i].partialDecryptions[j].m[index]
        = resp[i].secretShare*stmt.ciphertexts[j].CTXu;
      RoundModP(msg[i].partialDecryptions[j].m[index]);
      msg[i].partialDecryptions[j].m[1-index] = resp[i].partialDecryption[j];
      ZZ_pE message = stmt.ciphertexts[j].CTXv -  msg[i].partialDecryptions[j].m[0] - msg[i].partialDecryptions[j].m[1];
      RoundModP(message);
      if (!IsZero(stmt.messages[j]-message)){correctness = false;}}
  }
  if (hash==HashCommitMessage(msg) and shortness and correctness){
    cout << "Accept Decryption" << "\n";}
    else {cout << "Reject Decryption" << "\n";}}

string HashCommitMessage(Vec<CommitMessage> &msg){
  string returnString = "VerifiableDecryptionInTheHead";
  for(int i=0; i < lambda; i++){
    returnString += ZZ_pEToString(msg[i].pubKeyShare[0]);
    returnString += ZZ_pEToString(msg[i].pubKeyShare[1]);
    returnString += ZZ_pEToString(msg[i].secretCom[0].com);
    returnString += ZZ_pEToString(msg[i].secretCom[1].com);
    returnString += ZZ_pEToString(msg[i].errorCom[0].com);
    returnString += ZZ_pEToString(msg[i].errorCom[1].com);
    for(int j=0; j < tau; j++){
      returnString += ZZ_pEToString(msg[i].partialDecryptions[j].m[0]);
      returnString += ZZ_pEToString(msg[i].partialDecryptions[j].m[1]);
}}  return sha256(returnString);}
