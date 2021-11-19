
#include "encryption.h"

void SampleMessage(ZZ_pE &m){
  ZZ_pX f = ZZ_pX(INIT_MONO, N-1);
  for(int i = 0; i < N; i++){
    SetCoeff(f,i,RandomBnd(p));
  } m = to_ZZ_pE(f);}

void KeyGenEnc(EncKey &encKey){
  encKey.PKa = random_ZZ_pE();
  SampleBounded(encKey.SKs,smallB), SampleBounded(encKey.SKe,smallB);
  encKey.PKb = encKey.PKa*encKey.SKs+ZZ_pE(p)*encKey.SKe;}

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
