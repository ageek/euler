#include <iostream>
#include <vector> 
#include <set>
#include <cmath>

//Goldbach's other conjecture
//Problem 46
//
//It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.
//
//9 = 7 + 2×1^2
//15 = 7 + 2×2^2
//21 = 3 + 2×3^2
//25 = 7 + 2×3^2
//27 = 19 + 2×2^2
//33 = 31 + 2×1^2
//
//It turns out that the conjecture was false.
//
//What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?
//
//core algo:
//P = p0 + 2*j*j
//0. precalculate primes till some max say 50k
//1. check all possible values of j: bail out when P-2*j* is prime
//2.print when 1. fails

int main() {
    //precalculate primes till some max
    int max=500000;
    std::set<int> primes;
    primes.insert(2);
    for(int i=3; i<=max; i+=2) {
        bool res = true;
        for(auto p: primes) {
            //this check is for speedup, else will be 10x slower
            //prime p is too large to be a divisor
            if(p*p >i)
                break;

            if(i %p==0) {
                res = false;
                break;
            }
        }
        if(res)
            primes.insert(i);
    }

    for(int i=9; i<=max; i+=2 ){
        //proceed only if not prime
        if(primes.count(i)!=0) 
            continue;
        //assume there is no prime that fits the condition
        bool possible = false;
        for(int j=1; 2*j*j < i; j++) {
            auto remaining = i - 2*j*j;
            //found a combination, so conjecture still holds true
            if(primes.count(remaining) > 0){
                possible = true;
                break;
            }
        }
        //thru the loop, but could not find a combination...cojecture fails
        //print and bail out!
        if(!possible) {
            std::cout << i << std::endl;
            break;
        }
    }
    return 0;
}

