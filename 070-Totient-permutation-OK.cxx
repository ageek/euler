#include <iostream>
#include <vector> 
#include <set>
#include <cmath>
#include <algorithm>
//Totient permutation
//Problem 70
//
//Euler's Totient function, φ(n) [sometimes called the phi function], is used to determine the number of positive numbers less than or equal to n which are relatively prime to n. For example, as 1, 2, 4, 5, 7, and 8, are all less than nine and relatively prime to nine, φ(9)=6.
//The number 1 is considered to be relatively prime to every positive number, so φ(1)=1.
//
//Interestingly, φ(87109)=79180, and it can be seen that 87109 is a permutation of 79180.
//
//Find the value of n, 1 < n < 107, for which φ(n) is a permutation of n and the ratio n/φ(n) produces a minimum.
//
//ref: stbrummes for phi()

//(base) topo@topobox:~/myRev/cpp/euler$ gpp -O3 070-Totient-permutation.cxx
//(base) topo@topobox:~/myRev/cpp/euler$ time ./a.out
//783169
//
//real	0m0.656s
//user	0m0.609s
//sys	0m0.000s
//(base) topo@topobox:~/myRev/cpp/euler$


// global vector of primes``
std::vector<unsigned long long> primes;
//returns prime factors of num
std::set<std::pair<unsigned long long, unsigned long long>>  primeFactors(unsigned long long num) {
    std::set<std::pair<unsigned long long, unsigned long long>> factors;
    for(auto p : primes) {
        unsigned long long t=0;
        while(num%p==0) {
            num /= p;
            t++;
        }
        if(t>0)
            factors.insert(std::make_pair(p, t));
    }
    return factors;
}
// convert num to signature i.e. occurence count of each digit from 0 to 9
// placed at corresponding index value
// e.g. 66458 ->0000112010
std::string signature(int num) {
    std::string result ("0000000000");
    while(num>0) {
        int t = num %10;
        result[t] = result[t] + 1 ;
        num /= 10;
    }
    return result;
}


//Slower method, use phi instead (4x faster)
unsigned long long phi2(unsigned long long num) {
    std::set<std::pair<unsigned long long, unsigned long long>> pFactors = primeFactors(num);
    //https://www.whitman.edu/mathematics/higher_math_online/section03.08.html
    //for prime p: phi(p^a) = p^a - p^(a-1)
    //A number x can be represented as its prime factors and then use the above formula
    //p.first  -> base
    //p.second -> exp
    unsigned long long result = 1;
    for(auto p: pFactors) {
        //std::cout << p.first << "^" << p.second << std::endl;
        result *= (pow(p.first, p.second) - pow(p.first, p.second-1));
    }
    return result;
}

// 4X faster than phi2, refer wiki article for details
// The original formula for the totient is (see https://en.wikipedia.org/wiki/Euler%27s_totient_function ):
// `result = x * (1 - 1/prime1) * (1 - 1/prime2) * (1 - 1/prime3) * ...`
// e.g. if x == 10
// `result = 10 * (1 - 1/2) * (1 - 1/5) = 4`
//
// whenever we find a prime factor ''p'', then ''result -= result/p''.
// For `phi(10)` we have the prime factors `2` and `5`
// `10 * (1 - 1/2) * (1 - 1/5)`
// `= (10 * (1 - 1/2)) * (1 - 1/5)`
// `= (10 - 10/2) * (1 - 1/5)` ==> ''result -= result/2''
// `= 5 * (1 - 1/5)`
// `= 5 - 5/5` ==> ''result -= result/5''
// `= 4`

unsigned long long phi(unsigned long long x) {

    auto result = x; 
    auto remaining = x;
    for(auto p: primes) {
        if(p*p > remaining)
            break;
        if(remaining % p !=0)
            continue;
        //remove multiple occurences of prime factor
        do {
            remaining /= p;
        }while(remaining %p ==0);

        result = result - result/p;
    }
    //if the number is a prime
    if (result==x)
        return x-1;
    //we checked till prime factos(x) <=sqrt(x), check the last if remaining>1
    //there might exist one prime factor > sqrt(x)
    if(remaining>1)
        return result - result/remaining;
    //if remaining=1, we found all prime factors and all factors <= sqrt(x)
    else
        return result;
}

int main() {
    // max = 10^7-1;
    unsigned long long max = 999999;
    //calculate primes till sqrt(max)
    primes.push_back(2);
    for(unsigned long long i=3; i*i<=max; i+=2) {
        bool isPrime=true;
        for(auto p: primes) {
            if(p*p>i)
                break;
            if(i%p==0) {
                isPrime = false;
                break;
            }
        }
        if(isPrime)
            primes.push_back(i);
    }

    double minRatio = max;
    unsigned int minN = 2;
    //check all nums from 11 to 1o^7-1 and see if phi(x) has same signature as x
    for(unsigned long long n=11; n<=max; n++) {
        //Using phi2 is ~4X slower than using phi
        unsigned long phi_n = phi(n);
        double ratio = n/(double)phi_n;
        // IMP Note: 
        // calculating ratio is faster than calculating signature
        // so check ratio for all n's, ony when ratio is better than previous min, check signature(which is a costly affiar)
        // checking signature first then ratio will slow down terribly
        if(ratio >= minRatio)
            continue;
        //ratio < minRatio, check if signature matches
        if(signature(n) == signature(phi_n)) {
            //std::cout << n << ":" << phi_n << ":" << n/(double)phi_n << std::endl;
            //found a better ratio, save it
            minRatio = ratio;
            minN = n;
        }
    }
    std::cout << minN << std::endl;
    return 0;
}

