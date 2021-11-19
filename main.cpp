
#include "zeroknowledge.h"
#include "protocol.h"

void PrintProtocolTimings(const clock_t begin, const clock_t end){
  double elapsed_secs = double(end - begin)/CLOCKS_PER_SEC;
  cout << "\n";
  cout << "Decryption Protocol:"<< "\n";
  cout << "Soundness: 2^-" << lambda << "\n";
  cout << "Ciphertexts: " << tau << "\n";
  cout << "\n";
  cout << "Proof time: " <<elapsed_secs << " sec\n";
  cout << "Time / ctx: " <<elapsed_secs/(lambda*tau) << " sec\n";
  cout << "\n";
}

void PrintZKPTimings(const clock_t begin, const clock_t end){
  double elapsed_secs = double(end - begin)/CLOCKS_PER_SEC;
  cout << "\n";
  cout << "Zero-Knowledge Protocol:"<< "\n";
  cout << "Soundness: (2/3)^-" << mu << "\n";
  cout << "Number of proofs: " << 2*lambda << "\n";
  cout << "\n";
  cout << "Proof time: " <<elapsed_secs << " sec\n";
  cout << "Time / proof: " <<elapsed_secs/(2*lambda*mu) << " sec\n";
  cout << "\n";
}

int main()
{
  // Define variables
  EncKey encKey;
  ComKey comKey;
  Statement stmt;
  string hash;

  Vec<CommitMessage> comMsg;
  BinaryChallenge binaryChlg;
  Vec<Response> resp;

  Mat<ProofMessage> proofMessage;
  Vec<TernaryChallenge> ternaryChlg;
  Mat<Proof> zkProof;

  clock_t begin, end;

  // Initialize keys, message and response
  InitializeDecryption(encKey,comKey,comMsg,resp);

  // Sample tau messages and ciphertexts
  CreateStatement(stmt,encKey);

  begin = clock();
  // Create the commit message
  CreateCommitMessage(comMsg,hash,encKey,comKey,stmt);

  // Create lambda binary challenges
  CreateChallenge(binaryChlg);

  // Create the response message
  CreateResponseMessage(resp,comMsg,binaryChlg);
  end = clock();

  // Print parameters and timings
  PrintProtocolTimings(begin,end);

  // Verify the decryption proof
  VerifyResponseMessage(stmt,hash,binaryChlg,resp,encKey.PKa,comKey);

  // Initialize proofMessage, ternaryChlg and zkProof
  InitializeZKProof(proofMessage,ternaryChlg,zkProof);

  begin = clock();
  CreateZKProofMessage(proofMessage, comKey.PK, comMsg, binaryChlg);

  // Create mu ternary challenges
  CreateTernaryChallenge(ternaryChlg);

  // Create the proof message
  CreateZKProof(zkProof, proofMessage, ternaryChlg);
  end = clock();

  // Print parameters and timings
  PrintZKPTimings(begin,end);

  // Verify the shortness proof
  VerifyZKProof(zkProof, ternaryChlg, comKey.PK, resp);
}
