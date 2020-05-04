#include <iostream>
#include <vector> 
#include <algorithm>

//Pandigital prime
//Problem 41
//
//We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.
//
//What is the largest n-digit pandigital prime that exists?
//
//core algo:
//0.since we are looking for the max n-digit pandigital, check the permutations from max to min
//1.when we find on panPrime, bail out --> this is the max 
//2.use std::prev_permutation starting from max
//3.iterate over all permutations of length n to 2
//4.check if a prime is pandigital upto length x, where n> x > 2
//
//
//I/O: Enable O3 optimization for g++ 
//(base) topo@topobox:~/myrep/euler$ gpp -O3 41-Pandigital-prime-terribly-slow-13s-ok.cxx
//(base) topo@topobox:~/myrep/euler$ time ./a.out
//7652413
//
//real	0m1.940s
//user	0m1.928s
//sys	0m0.001s
//(base) topo@topobox:~/myrep/euler$ gpp 41-Pandigital-prime-terribly-slow-13s-ok.cxx
//(base) topo@topobox:~/myrep/euler$ time ./a.out
//7652413
//
//real	0m16.329s
//user	0m16.242s
//sys	0m0.004s
//(base) topo@topobox:~/myrep/euler$
//

//not used here
bool isPrime(int num) {
    if(num <= 1)
        return false;

    bool result = true;
    for(int x=2; x*x <= num; x++) {
        if(num %x ==0){
            result = false;
        }
    }
    return result;
}

int main() {
    //precalculate all primes till x*x <= 987654321
    std::vector<int> primes;
    //push the base elements
    primes.push_back(2);
    primes.push_back(3);
    primes.push_back(5);
    primes.push_back(7);
    for(int i=11; i*i <= 987654321 ; i++) {
        bool p = true;
        for(auto a: primes){
            // no divisors possible, bail out
            if(a * a > i)
                break;
            if(i % a == 0){
                p = false;
                break;
            }
        }
        if(p)
            primes.push_back(i);
    }
    // for each size of digits i.e. 9-pandigital, 8-pandigital etc...
    std::string current = "987654321";
    while(current.size() > 1){

        do {
            int a = std::stoi(current);
            //std::cout << a << std::endl;
            if(a%2 !=0) {
                bool t = true;
                for(auto p : primes) {
                    if(p *p > a)
                        break;
                    if(a % p == 0)
                        t = false;
                }
                if(t) {
                    std::cout << a << std::endl;
                    //Found one, bail out!
                    return 0;
                }
            }
        } while(std::prev_permutation(current.begin(), current.end()));
        //remove one char for next iteration of permutations
        current.erase(0,1);
    }

    return 0;
    }

