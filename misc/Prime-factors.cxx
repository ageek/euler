#include <iostream>
#include <vector> 
#include <set>

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
    //for(auto p: primes)
    //    std::cout << p << ",";

    //for(auto x: primeFactors(9843984)) {
    for(auto x: primeFactors(823872)) {
        std::cout << x.first << "^" << x.second << ",";
    }
    std::cout << std::endl;
    return 0;
}

