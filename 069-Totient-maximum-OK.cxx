#include <iostream>
#include <vector> 
#include <set>
#include <algorithm>

//Totient maximum
//Problem 69
//
//Euler's Totient function, φ(n) [sometimes called the phi function], is used to determine the number of numbers less than n which are relatively prime to n. For example, as 1, 2, 4, 5, 7, and 8, are all less than nine and relatively prime to nine, φ(9)=6.
//n 	Relatively Prime 	φ(n) 	n/φ(n)
//2 	1 	                1 	    2
//3 	1,2 	            2 	    1.5
//4 	1,3 	            2 	    2
//5 	1,2,3,4 	        4 	    1.25
//6 	1,5 	            2 	    3
//7 	1,2,3,4,5,6 	    6 	    1.1666...
//8 	1,3,5,7 	        4 	    2
//9 	1,2,4,5,7,8 	    6 	    1.5
//10 	1,3,7,9 	        4 	    2.5
//
//It can be seen that n=6 produces a maximum n/φ(n) for n ≤ 10.
//
//Find the value of n ≤ 1,000,000 for which n/φ(n) is a maximum
//Core Idea: 
//  1.Euler's totient function is a multiplicative function, meaning that if two numbers m and n are relatively prime, then φ(mn) = φ(m)φ(n).
//  2.https://en.wikipedia.org/wiki/Euler%27s_totient_function
//  3. n/φ(n) is maximized when φ(n) is minimized and n maximized 
//  4. result is the product of all primes, where product <=max 
//  I/O:
//  (base) topo@topobox:~/myRev/cpp/euler$ gpp -O3 069-Totient-maximum.cxx
//(base) topo@topobox:~/myRev/cpp/euler$ time ./a.out
//510510
//
//real	0m0.003s
//user	0m0.003s
//sys	0m0.000s
//(base) topo@topobox:~/myRev/cpp/euler$


int main() {
    unsigned int max=1000000;
    std::set<unsigned int> primes;
    primes.insert(2);
    for(int i=3; i<=200; i+=2) {
        bool isPrime = true;
        for(auto p: primes) {
            if(p*p > i)
                break;

            if(i%p ==0)
                isPrime = false;
        }
        if(isPrime) 
            primes.insert(i);
    }

    unsigned long long result = 1;
    for(auto p: primes) {
        unsigned long long current = result * p ;
        if(current >= max)
            break;
        result *= p;
    }
    std::cout << result << std::endl;
    return 0;
}

