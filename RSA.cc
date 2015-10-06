// ECE4122/6122 RSA Encryption/Decryption assignment
// Fall Semester 2015
// Yushan Cai

#include <iostream>
#include "RSA_Algorithm.h"

using namespace std;

int main()
{
  // Instantiate the one and only RSA_Algorithm object
  RSA_Algorithm RSA;
  
  //Initialize class for random message generation
  gmp_randclass random_M(gmp_randinit_default);

  //Start with sz as 32 bits, and double the size for each iteration up to and including 1024 bits
  for (int sz = 32; sz <= 1024; sz *= 2)
  {

    //Compute 10 different public/private key pairs
    for (int i = 0; i < 10; ++i)
    {
      RSA.GenerateRandomKeyPair(sz);

      //Call the PrintNDE function
      RSA.PrintNDE();

      //Compute 10 random messages of size less than sz ∗ 2 bits
      //using size sz
      for (int j = 0; j < 10; ++j)
      {
        mpz_class M = random_M.get_z_bits(sz);

        //If the returned random number is larger than n, discard that random number and get another
        while (M > RSA.n)
        {
          M = random_M.get_z_bits(sz);
        }

        //Call the PrintM function.
        RSA.PrintM(M);

        //Compute the ciphertext C
        mpz_class C = RSA.Encrypt(M);

        //Call the PrintC function.
        RSA.PrintC(C);

        //Decrypt the ciphertext message
        M = RSA.Decrypt(C);

        //Verify the decrypted message is identical to the original plaintext message
        RSA.PrintM(M);
      }
    }
  }
}