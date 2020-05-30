#include <iostream>
#include <vector> 
#include <set>

//Prime pair sets
//Problem 60
//
//The primes 3, 7, 109, and 673, are quite remarkable. By taking any two primes and concatenating them in any order the result will always be prime. For example, taking 7 and 109, both 7109 and 1097 are prime. The sum of these four primes, 792, represents the lowest sum for a set of four primes with this property.
//
//Find the lowest sum for a set of five primes for which any two primes concatenate to produce another prime.
//
//core algo:
//1. find primes till some max value, say 20k
//2. find 2s: for each prime:a, find b from the set such that ab and ba are both prime
//3. find 3s: now find c from the set such that bc & cb are all primes (ab, ba & ac, ca already checked in last step)
//4. find 4s: continue this way: find d and ensure bd, db & cd, dc are primes
//5. find 5s: find e such that : be, ce, de & eb, ec, ed are all primes 
//
//Note:1. A faster and efficient primality testing is the crux of the problem. Using a naive primality testing slows down the overall check
//          whereas a faster one like :Miller-Rabin test speeds up everything 
//I/O:
//(base) topo@topobox:~/euler$ gpp -O3 060-Prime-pair-set-Miller-Rabin-v3-ok.cxx
//(base) topo@topobox:~/euler$ time ./a.out
//26033
//
//real	0m3.613s
//user	0m3.525s
//sys	0m0.000s
//(base) topo@topobox:~/euler$

bool isPrime(unsigned long long p);
//global sums set to store all sums
std::set<unsigned int> sums;

//Primality testing - Naive 
//Extremely slow in this case
//Not used : User Miller Rabin test instead
bool isPrimeSlow(int num) {
    if(num==1)
        return false;

    bool isPrime=true;
    for(int i=2; i*i<=num; i++) {
        if(i*i>num)
            break;
        if(num % i==0) {
            isPrime = false;
            break;
        }
    }
    return isPrime;
}
// merge two numbers, "append their digits"
unsigned long long append(unsigned long long a, unsigned long long b)
{
    // append(34,56) -> 3456
    unsigned long long shift = 10;
    while (shift <= b)
        shift *= 10;
    return a * shift + b;
}

// check if ab and ba are both primes when appended together
bool isConcatPrime(unsigned long long a, unsigned long long b)
{
    //return isPrimeSlo(append(a, b)) && isPrimeSlo(append(b, a));
    return isPrime(append(a, b)) && isPrime(append(b, a));
}

void check5s(unsigned long long first, std::vector<unsigned int>& candidates) {
    //a : first
    //b : can be any of candidates
    //c : find from candidates such that bc/cb is prime
    for(int indexB=0; indexB<=candidates.size(); indexB++) {
        for(int indexC=indexB+1; indexC<=candidates.size(); indexC++) {
            if(isConcatPrime(candidates[indexB], candidates[indexC])){
                //d: find from candidates such that bd/db, cd/dc are all primes
                for(int indexD=indexC+1; indexD<=candidates.size(); indexD++) {
                    if(isConcatPrime(candidates[indexB], candidates[indexD]) &&
                            isConcatPrime(candidates[indexC], candidates[indexD])) {
                        //e: find from candidates such such be/eb, ce/ec, de/ed are all primes 
                        for(int indexE=indexD+1; indexE<=candidates.size(); indexE++) {
                            if(isConcatPrime(candidates[indexB], candidates[indexE]) &&
                                    isConcatPrime(candidates[indexC], candidates[indexE]) &&
                                    isConcatPrime(candidates[indexD], candidates[indexE])) {
                                unsigned int s = first + candidates[indexB] + candidates[indexC] +candidates[indexD] + candidates[indexE] ;
                                sums.insert(s);
                                //std::cout << "found: " << first << "," << candidates[indexB] << "," << candidates[indexC] << "," 
                                //    << candidates[indexD] << "," << candidates[indexE] << std::endl;
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int max=20000;
    std::vector<int> primes;
    primes.push_back(2);
    for(int i=3; i<=max; i+=2) {
        bool prime = true;
        for(auto p: primes) {
            if(p*p > i)
                break;
            if(i %p ==0) {
                prime=false;
                break;
            }
        }
        if(prime)
            primes.push_back(i);
    }

    // we need to find 5 primes a, b, c, d, e such that any two concat(both ways) produces a prime
    //
    //1. find a: all primes in primes[] 
    for(int indexA=0; indexA< primes.size(); indexA++) {
        //2. find b: such that ab and ba are both prime
        std::vector<unsigned int> candidates;
        for(int indexB=indexA+1; indexB< primes.size(); indexB++) {
            if(isConcatPrime(primes[indexA], primes[indexB])) {
                candidates.push_back(primes[indexB]);
            }
        }
        //now check we've a 5-pair set in primes[indexA] & candidates
        check5s(primes[indexA], candidates);
    }
    //print smallest sum
    std::cout << *sums.begin() << std::endl;

    return 0;
}

//Primality testing using Miller-Rabin test
//Code ref: https://github.com/stbrumme/euler/blob/master/euler-0060.cpp

// return (a*b) % modulo
unsigned long long mulmod(unsigned long long a, unsigned long long b, unsigned long long modulo)
{
#ifdef __GNUC__
  // use GCC's optimized 128 bit code
  return ((unsigned __int128)a * b) % modulo;
#endif

  // (a * b) % modulo = (a % modulo) * (b % modulo) % modulo
  a %= modulo;
  b %= modulo;

  // fast path
  if (a <= 0xFFFFFFF && b <= 0xFFFFFFF)
    return (a * b) % modulo;

  // we might encounter overflows (slow path)
  // the number of loops depends on b, therefore try to minimize b
  if (b > a)
    std::swap(a, b);

  // bitwise multiplication
  unsigned long long result = 0;
  while (a > 0 && b > 0)
  {
    // b is odd ? a*b = a + a*(b-1)
    if (b & 1)
    {
      result += a;
      if (result >= modulo)
        result -= modulo;
      // skip b-- because the bit-shift at the end will remove the lowest bit anyway
    }

    // b is even ? a*b = (2*a)*(b/2)
    a <<= 1;
    if (a >= modulo)
      a -= modulo;

    // next bit
    b >>= 1;
  }

  return result;
}

// return (base^exponent) % modulo
unsigned long long powmod(unsigned long long base, unsigned long long exponent, unsigned long long modulo)
{
  unsigned long long result = 1;
  while (exponent > 0)
  {
    // fast exponentation:
    // odd exponent ? a^b = a*a^(b-1)
    if (exponent & 1)
      result = mulmod(result, base, modulo);

    // even exponent ? a^b = (a*a)^(b/2)
    base = mulmod(base, base, modulo);
    exponent >>= 1;
  }
  return result;
}

// Miller-Rabin-test
bool isPrime(unsigned long long p)
{
  // some code from             https://ronzii.wordpress.com/2012/03/04/miller-rabin-primality-test/
  // with optimizations from    http://ceur-ws.org/Vol-1326/020-Forisek.pdf
  // good bases can be found at http://miller-rabin.appspot.com/

  // trivial cases
  const unsigned int bitmaskPrimes2to31 = (1 <<  2) | (1 <<  3) | (1 <<  5) | (1 <<  7) |
                                          (1 << 11) | (1 << 13) | (1 << 17) | (1 << 19) |
                                          (1 << 23) | (1 << 29); // = 0x208A28Ac
  if (p < 31)
    return (bitmaskPrimes2to31 & (1 << p)) != 0;

  if (p %  2 == 0 || p %  3 == 0 || p %  5 == 0 || p % 7 == 0 || // divisible by a small prime
      p % 11 == 0 || p % 13 == 0 || p % 17 == 0)
    return false;

  if (p < 17*19) // we filtered all composite numbers < 17*19, all others below 17*19 must be prime
    return true;

  // test p against those numbers ("witnesses")
  // good bases can be found at http://miller-rabin.appspot.com/
  const unsigned int STOP = 0;
  const unsigned int TestAgainst1[] = { 377687, STOP };
  const unsigned int TestAgainst2[] = { 31, 73, STOP };
  const unsigned int TestAgainst3[] = { 2, 7, 61, STOP };
  // first three sequences are good up to 2^32
  const unsigned int TestAgainst4[] = { 2, 13, 23, 1662803, STOP };
  const unsigned int TestAgainst7[] = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022, STOP };

  // good up to 2^64
  const unsigned int* testAgainst = TestAgainst7;
  // use less tests if feasible
  if (p < 5329)
    testAgainst = TestAgainst1;
  else if (p < 9080191)
    testAgainst = TestAgainst2;
  else if (p < 4759123141ULL)
    testAgainst = TestAgainst3;
  else if (p < 1122004669633ULL)
    testAgainst = TestAgainst4;

  // find p - 1 = d * 2^j
  auto d = p - 1;
  d >>= 1;
  unsigned int shift = 0;
  while ((d & 1) == 0)
  {
    shift++;
    d >>= 1;
  }

  // test p against all bases
  do
  {
    auto x = powmod(*testAgainst++, d, p);
    // is test^d % p == 1 or -1 ?
    if (x == 1 || x == p - 1)
      continue;

    // now either prime or a strong pseudo-prime
    // check test^(d*2^r) for 0 <= r < shift
    bool maybePrime = false;
    for (unsigned int r = 0; r < shift; r++)
    {
      // x = x^2 % p
      // (initial x was test^d)
      x = powmod(x, 2, p);
      // x % p == 1 => not prime
      if (x == 1)
        return false;

      // x % p == -1 => prime or an even stronger pseudo-prime
      if (x == p - 1)
      {
        // next iteration
        maybePrime = true;
        break;
      }
    }

    // not prime
    if (!maybePrime)
      return false;
  } while (*testAgainst != STOP);

  // prime
  return true;
}

