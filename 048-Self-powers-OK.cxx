#include <iostream>
#include <vector> 
#include <set>
#include <algorithm>

//Self powers
//Problem 48
//
//The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.
//
//Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
//
//core algo:
//1. for each i=1 to 1000
//2.    calculate modularExponentiantion(base, exp, 10^9)
//3.    after each addition of i^i, do a % with 10^9
//I/O:
//(base) topo@topobox:~/myRev/cpp/euler$ time echo 1000|./a.out
//9110846700
//
//real	0m0.008s
//user	0m0.007s
//sys	0m0.000s
//(base) topo@topobox:~/myRev/cpp/euler$ time echo 10000|./a.out
//6237204500
//
//real	0m0.313s
//user	0m0.289s
//sys	0m0.000s
//(base) topo@topobox:~/myRev/cpp/euler$
//
//Note: 1.There are other nifty tricks e.g.https://en.wikipedia.org/wiki/Exponentiation_by_squaring 
//        that can be employed for speeding up operations 
//      2.But, for current scenario till n=1000, naive modulo technique is pretty fast 

//calculates (base ^ exponent) % modulo 
unsigned long moduloExp(unsigned long base, unsigned long exponent, unsigned long modulo) {
    // base ^exp = base x base x base ....exp times
    unsigned long result = 1;
    for(int i=1; i<=exponent; i++) {
        // a^b % x = (a * a) % x ...repeat b times
        result = ( result * base ) % modulo;
    }
    return result % modulo;
}

int main() {
    // for current problem it can be set to 1000
    int max;
    std::cin >> max;

    unsigned long modulo = 10000000000;

    unsigned long result = 0;
    for(int i=1; i<=max; i++) {
        int base = i; 
        int exp  = i;
        result = (result + moduloExp(base, exp, modulo)) % modulo;
    }

    std::cout << result << std::endl;
    return 0;
}

