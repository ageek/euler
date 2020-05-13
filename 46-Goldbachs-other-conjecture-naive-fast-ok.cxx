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

int main() {
    //precalculate primes till some max
    int max=6000;
    std::set<int> primes;
    primes.insert(2);
    for(int i=3; i<=max; i+=2) {
        bool res = true;
        for(auto a: primes) {
            if(i %a==0) 
                res = false;
        }
        if(res)
            primes.insert(i);
    }
    //    for(auto a:primes)
    //        std::cout << a << ",";
    //
    //check from reverse and pick the previous prime and try to convert remaining as 2x some^2
    //check for non-prime/composite and odd number
    for(int a=9; a<=max; a+=2 ){
        //proceed only if not prime
        //assume a is not Goldbachs, lets check if its trur
        bool check = false;
        if(primes.count(a)==0) {
            for(auto z:primes){
                if(z>a)
                    break;
                //pick the prime no smaller than this num
                auto x = primes.lower_bound(z);
                auto p = *x--;
                int rem = a-p;
                //proceed if rem is even
                if(rem %2==0) {
                    int sqr = rem/2;
                    int s = sqrt(sqr);
                    if(s*s == sqr) {
                        //std::cout << "Goldbachs:" << a << "=" << p << "+" << "2x" << s <<"^2" << std::endl; 
                        check = true;
                        break;
                    }
                }
            }
        }
        if(primes.count(a)==0 && !check){
            //found an element which falsifies Goldbach's conjecture
            std::cout << a << std::endl;
            //bail out
            return 0;
        }
    }
    return 0;
}

