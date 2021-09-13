
#include "sha2.h"
#include "classes.h"

string ZZ_pEToString(const ZZ_pE &z) {
    string returnString = ""; long a;
    ZZ_pX f = conv<ZZ_pX>(z);
    for(int i = 0; i < N; i++){
      conv(a,rep(coeff(f,i)));
      returnString += to_string(a);
    } return returnString;}

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
      returnString += ZZ_pEToString(msg[i].partialDecryptions[j].t[0]);
      returnString += ZZ_pEToString(msg[i].partialDecryptions[j].t[1]);
}}  return sha256(returnString);}

void SampleBounded(ZZ_pE &r, const long &bound){
  ZZ_pX f = ZZ_pX(INIT_MONO, N-1);
  for(int i = 0; i < N; i++){
    SetCoeff(f,i,RandomBnd(2*bound+1)-bound);
  } r = to_ZZ_pE(f);}

void SampleMessage(ZZ_pE &m){
  ZZ_pX f = ZZ_pX(INIT_MONO, N-1);
  for(int i = 0; i < N; i++){
    SetCoeff(f,i,RandomBnd(p));
  } m = to_ZZ_pE(f);}

bool isBounded(const ZZ_pE &r, const double &bound){
  ZZ b = ZZ(0);
  ZZ_pX f = conv<ZZ_pX>(r);
  for(int i = 0; i < N; i++){
    ZZ t = conv<ZZ>(coeff(f,i));
    if (t - (t > q/2)*q > b) { b = t; }
  } return b <= ZZ(bound);}

void KeyGenEnc(EncKey &encKey){
  encKey.PKa = random_ZZ_pE();
  SampleBounded(encKey.SKs,smallB), SampleBounded(encKey.SKe,smallB);
  encKey.PKb = encKey.PKa*encKey.SKs+ZZ_pE(p)*encKey.SKe;}

void KeyGenCom(ComKey &comKey){
  comKey.PK = random_ZZ_pE();}

void Encrypt(Ciphertext &ctx, const EncKey &encKey, const ZZ_pE &m){
  ZZ_pE r,e1,e2;
  SampleBounded(r,smallB), SampleBounded(e1,smallB), SampleBounded(e1,smallB);
  ctx.CTXu = encKey.PKa*r+ZZ_pE(p)*e1, ctx.CTXv = encKey.PKb*r+ZZ_pE(p)*e2+m;}

void RoundModP(ZZ_pE &m){
  ZZ_pX f = conv<ZZ_pX>(m);
  for(int i = 0; i < N; i++){
    ZZ t = conv<ZZ>(coeff(f,i));
    SetCoeff(f,i,((t - (t > q/2)*q) % p + p) % p);
  } m = to_ZZ_pE(f);}

void Decrypt(ZZ_pE &m, const EncKey &encKey, const Ciphertext &ctx){
  m = ctx.CTXv - encKey.SKs*ctx.CTXu, RoundModP(m);}

void Commit(Commitment &commitment, const ComKey &comKey, const ZZ_pE &m){
  SampleBounded(commitment.open,smallB),
  commitment.message = m, commitment.com = comKey.PK*commitment.message+commitment.open;}
