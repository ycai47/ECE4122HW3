// RSA Assignment for ECE4122/6122 Fall 2015
//Yushan Cai

#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "RSA_Algorithm.h"

using namespace std;

// Constructor
RSA_Algorithm::RSA_Algorithm()
  : rng(gmp_randinit_default)
{
  // get a random seed for the random number generator
  int dr = open("/dev/random", O_RDONLY);
  if (dr < 0)
    {
      cout << "Can't open /dev/random, exiting" << endl;
      exit(0);
    }
  unsigned long drValue;
  read(dr, (char*)&drValue, sizeof(drValue));
  //cout << "drValue " << drValue << endl;
  rng.seed(drValue);
// No need to init n, d, or e.
}

// Generate key
void RSA_Algorithm::GenerateRandomKeyPair(size_t sz)
{
  //Declare p and q
  mpz_class p, q;

  //Make sure both numbers are random prime numbers.
  while(!mpz_probab_prime_p(p.get_mpz_t(), 100))
  { 
    p = rng.get_z_bits(sz); //returns random value of size sz
  }
  while(!mpz_probab_prime_p(q.get_mpz_t(), 100))
  { 
    q = rng.get_z_bits(sz);
  }

  //Calculate n
  n = p * q;

  //Calculate phi
  mpz_class phi = (p-1) * (q-1);

  //Declare class for greatest common divisor
  mpz_class gcd;

  //Generate a new random new d and update gcd while
  //d is not less than phi or gcd is not equal to 1
  do
  {
    d = rng.get_z_bits(sz * 2);
    mpz_gcd(gcd.get_mpz_t(), d.get_mpz_t(), phi.get_mpz_t());
  }
  while(d >= phi || gcd != 1);

  //Compute the inverse of d modulo phi as e
  mpz_invert(e.get_mpz_t(), d.get_mpz_t(), phi.get_mpz_t());
}

// Encrypt plaintext message M with (public) key pair n/e
mpz_class RSA_Algorithm::Encrypt(mpz_class M)
{
  //Declare ciphertext C
  mpz_class C;

  //Compute C = M^e mod n
  mpz_powm(C.get_mpz_t(), M.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());
  return C;
}

// Decrypt ciphertext message C with (private) key pair n/d
mpz_class RSA_Algorithm::Decrypt(mpz_class C)
{
  //Declare decrypted plaintext message M
  mpz_class M;

  //Compute M = C^d mod n
  mpz_powm(M.get_mpz_t(), C.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());
  return M;
}

void RSA_Algorithm::PrintND()
{ // Do not change this, right format for the grading script
  cout << "n " << n << " d " << d << endl;
}

void RSA_Algorithm::PrintNE()
{ // Do not change this, right format for the grading script
  cout << "n " << n << " e " << e << endl;
}

void RSA_Algorithm::PrintNDE()
{ // Do not change this, right format for the grading script
  cout << "n " << n << " d " << d << " e " << e << endl;
}

void RSA_Algorithm::PrintM(mpz_class M)
{ // Do not change this, right format for the grading script
  cout << "M " << M << endl;
}

void RSA_Algorithm::PrintC(mpz_class C)
{ // Do not change this, right format for the grading script
  cout << "C " << C << endl;
}