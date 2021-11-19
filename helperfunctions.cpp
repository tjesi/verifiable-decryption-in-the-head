
#include "helperfunctions.h"

string ZZ_pEToString(const ZZ_pE &z) {
    string returnString = ""; long a;
    ZZ_pX f = conv<ZZ_pX>(z);
    for(int i = 0; i < N; i++){
      conv(a,rep(coeff(f,i)));
      returnString += to_string(a);
    } return returnString;}

void SampleBounded(ZZ_pE &r, const long &bound){
  ZZ_pX f = ZZ_pX(INIT_MONO, N-1);
  for(int i = 0; i < N; i++){
    SetCoeff(f,i,RandomBnd(2*bound+1)-bound);
  } r = to_ZZ_pE(f);}

bool isBounded(const ZZ_pE &r, const double &bound){
  ZZ b = ZZ(0);
  ZZ_pX f = conv<ZZ_pX>(r);
  for(int i = 0; i < N; i++){
    ZZ t = conv<ZZ>(coeff(f,i));
    if (t - (t > q/2)*q > b) { b = t; }
  } return b <= ZZ(bound);}

Vec<ZZ_p> PolyToVec(const ZZ_pE &input){
  Vec<ZZ_p> output; output.SetLength(input.degree());
  ZZ_pX f = conv<ZZ_pX>(input);
  for (int i=0; i<output.length(); i++){output[i] = coeff(f,i);}
  return output;}

ZZ_pE VecToPoly(const Vec<ZZ_p> &input){
  ZZ_pX f;
  for (int i=0; i<input.length(); i++)
    {SetCoeff(f,i,input[i]);}
  return to_ZZ_pE(f);}

string HashPermutation(const vector<int> &perm){
  string returnString = "HashPermutation";
  for (int i=0; i<perm.size(); i++){
    returnString += to_string(perm[i]);}
  return sha256(returnString);}

string HashVector(const Vec<ZZ_p> &vec){
  string returnString = "HashVector"; long a;
  for (int i=0; i<vec.length(); i++){
    conv(a,rep(vec[i])); returnString += to_string(a);}
  return sha256(returnString);}

void SamplePermutation(vector<int> &perm){
  iota(perm.begin(), perm.end(), 0);
  random_device rd; mt19937 g(rd());
  shuffle(perm.begin(), perm.end(), g);}

void Permute(Vec<ZZ_p> &vOut, const vector<int> &perm, const Vec<ZZ_p> &vIn){
  for(int i = 0; i < vIn.length(); i++){
    vOut[i] = vIn[perm[i]];}}

bool VerifyBall(const Vec<ZZ_p> &vec){
  int zero = 0, one = 0, minusone = 0, l = vec.length();
  for(int i = 0; i < l; i++){
    if (vec[i] == ZZ_p(0)){zero++;}
    else if (vec[i] == ZZ_p(1)){one++;}
    else if (vec[i] == ZZ_p(-1)){minusone++;}}
  return zero==l/3 and one == l/3 and minusone == l/3;}

void Multiply(Vec<ZZ_p> &vOut, const ZZ_pE &a, const Vec<ZZ_p> &vIn){
  Vec<ZZ_p> temp1; temp1.SetLength(a.degree());
  Vec<ZZ_p> temp2; temp2.SetLength(a.degree());
  for(int i = 0; i < a.degree(); i++){
    temp1[i] = vIn[i]; temp2[i] = vIn[a.degree() + i];}
  vOut = PolyToVec(a*VecToPoly(temp1) + VecToPoly(temp2));}

void RandomVector(Vec<ZZ_p> &v){
  for(int i = 0; i < v.length(); i++){
    v[i] = random_ZZ_p();}}

void ShortVector(Vec<ZZ_p> &v){
  for(int i = 0; i < v.length(); i++){
    v[i] = ZZ_p(RandomBnd(3)-1);}}

void Expand(Vec<ZZ_p> &expand, const Vec<ZZ_p> &init){
  int zeroes = 0, ones = 0;
  for(int i = 0; i < expand.length(); i++){
    if (init.length() > i){expand[i] = init[i];
      if (init[i] == ZZ_p(0)){zeroes += 1;}
      else if(init[i] == ZZ_p(1)){ones += 1;}}
    else {
      if (zeroes < init.length()){
        expand[i] = ZZ_p(0); zeroes += 1;
      } else if(ones < init.length()){
        expand[i] = ZZ_p(1); ones += 1;
      } else {expand[i] = ZZ_p(-1);}}}}
