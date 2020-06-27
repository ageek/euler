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
//(base) topo@topobox:~/myRev/cpp/euler$ gpp -O3 060-Prime-pair-set-Miller-Rabin-ok.cxx
//(base) topo@topobox:~/myRev/cpp/euler$ time ./a.out 
//26033
//
//real	0m3.465s
//user	0m3.350s
//sys	0m0.004s
//(base) topo@topobox:~/myRev/cpp/euler$ gpp -O3 060-Prime-pair-set-Miller-Rabin-basic.cxx
//(base) topo@topobox:~/myRev/cpp/euler$ time ./a.out 
//26033
//
//real	2m6.535s
//user	2m3.714s
//sys	0m0.028s
//(base) topo@topobox:~/myRev/cpp/euler$ gpp -O3 060-Prime-pair-set-Naive-xtremely-slow-ok.cxx
//(base) topo@topobox:~/myRev/cpp/euler$ time ./a.out 
//26033
//
//real	0m44.791s
//user	0m43.185s
//sys	0m0.048s
//(base) topo@topobox:~/myRev/cpp/euler$
//Logically speaking, Mailler-rabin basic should run faster than Naive, but it is slowest. Seems the MillerRabin code needs some improvement
//Ref: https://ronzii.wordpress.com/2012/03/04/miller-rabin-primality-test/

long long mulmod(long long a, long long b , long long c)
{
    long long x=0,y=a%c;
    while(b>0)
    {
        if(b & 1)
        {
            x = (x+y)%c;
        }
        y=(y*2)%c;
        b>>=1;
    }
    return x%c;
}
long long modulo(long long a,long long b,long long c)
{
    long long y=a,x=1;
    while(b>0)
    {
        if(b & 1)
        {
            x = mulmod(x,y,c);
        }
        y = mulmod(y,y,c);
        b>>=1;
    }
    return x%c;
}
bool isPrime(long long p,int iterations=2)
{
    if(p<2) return false;
    if(p!=2 && p%2==0) return false;
    long long s = p-1;
    while(s%2==0)
    {
        s/=2;
    }
    //printf("%lld\n",s);
    for(int i=0; i<iterations; i++)
    {
        long long a = rand()%(p-1)+1,temp=s;
        long long mod = modulo(a,temp,p);
        //printf("%lld %lld %lld %lld\n",a,temp,p,mod);
        while(temp!=p-1 && mod!=1 && mod!=p-1)
        {
            mod = mulmod(mod,mod,p);
            temp*=2;
            //printf("%lld %lld\n",temp,mod);
        }
        if(mod!=p-1 && temp%2==0)
        {
            return false;
        }
 
    }
    return true;
}

//global sums set to store all sums
std::set<unsigned int> sums;

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



