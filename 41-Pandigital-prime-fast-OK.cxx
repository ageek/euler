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
//(base) topo@topobox:~/myrep/euler$ gpp 41-Pandigital-prime-fast-OK.cxx 
//(base) topo@topobox:~/myrep/euler$ time ./a.out 
//7652413
//
//real	0m0.285s
//user	0m0.247s
//sys	0m0.004s
//(base) topo@topobox:~/myrep/euler$ gpp -O3 41-Pandigital-prime-fast-OK.cxx 
//(base) topo@topobox:~/myrep/euler$ time ./a.out 
//7652413
//
//real	0m0.067s
//user	0m0.037s
//sys	0m0.000s
//(base) topo@topobox:~/myrep/euler$
//

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
    // for each length of digits i.e. 9-pandigital, 8-pandigital etc. check if its prime
    //
    int x=0;
    while(x < 8){
        std::string current = "987654321";
        //erase one char at a time
        //and check all permutations for the modified string: current
        current.erase(0,x);
        do {
            int a = std::stoi(current);
            //odd check to speed up
            if(a%2 !=0) {
                bool t = true;
                for(auto p : primes) {
                    if(p *p > a)
                        break;
                    if(a % p == 0){
                        t = false;
                        break; 
                    }
                }
                if(t) {
                    //Found one, bail out!
                    std::cout << a << std::endl;
                    return 0;
                }
            }
        } while(std::prev_permutation(current.begin(), current.end()));

        x++;
    }

    return 0;
    }

