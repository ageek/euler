#include <iostream>
#include <vector> 
#include <set>
//Largest prime factor
//Problem 3
//
//The prime factors of 13195 are 5, 7, 13 and 29.
//
//What is the largest prime factor of the number 600851475143 ?
//
//I/O:
//(base) topo@topobox:~/myRev/cpp/euler$ gpp 003-Largest-prime-factor.cxx
//(base) topo@topobox:~/myRev/cpp/euler$ ./a.out
//6857
//(base) topo@topobox:~/myRev/cpp/euler$

// global vector of primes``
std::vector<unsigned long long> primes;
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

int main() {
    unsigned long long max = 99999;
    primes.push_back(2);
    for(unsigned long long i=3; i<=max; i++) {
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

    unsigned long long largest = 0;
    for(auto x: primeFactors(600851475143)) {
        if(x.first > largest)
            largest=x.first;
    }
    std::cout << largest << std::endl;
    return 0;
}

