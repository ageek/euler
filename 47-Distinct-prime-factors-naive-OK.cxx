#include <iostream>
#include <vector> 
#include <set>

//Distinct primes factors
//Problem 47
//
//The first two consecutive numbers to have two distinct prime factors are:
//
//14 = 2 × 7
//15 = 3 × 5
//
//The first three consecutive numbers to have three distinct prime factors are:
//
//644 = 2² × 7 × 23
//645 = 3 × 5 × 43
//646 = 2 × 17 × 19.
//
//Find the first four consecutive integers to have four distinct prime factors each. What is the first of these numbers?
//
//
//core algo:
//1. check prime fac count of all numbers till some max value (say 50k)
//2. check for 4 consecutive nos with 4 distinct prime factors, 
//Note: Brute force is fast enough, not doing any optimization
//
//I/O:
//(base) topo@topobox:~/myRev/cpp/euler$ gpp -O3 Distinct-prime-factors.cxx
//(base) topo@topobox:~/myRev/cpp/euler$ time ./a.out
//134043
//
//real	0m0.164s
//user	0m0.129s
//sys	0m0.001s
//(base) topo@topobox:~/myRev/cpp/euler$

std::set<int>  primeFactors(int num) {
    std::set<int> factors;
    for(int i=2; i*i <=num; i++) {
        while( num % i==0 ) {
            factors.insert(i);
            num /= i;
        }
    }
    //insert the last val of num (last factor)
    factors.insert(num);
    return factors;
}

int main() {
    int max=500000;

//    //pre-calculate primes till 1000
//    std::vector<int> primes;
//    primes.push_back(2);
//    for(int i=3; i<=max; i+=2) {
//        bool t =true;
//        for(auto p: primes) {
//            if(p*p > i)
//                break;
//            if(i%p==0) {
//                t=false;
//                break;
//            }
//        }
//        if(t)
//            primes.push_back(i);
//    }

    //check all upto 50k digit numbers : 4 consecutive to have 4 distinct prime factors 
    int span=4;
    for(int i=600; i<=max; ) {
        int t=span;
        int j=i;
        while(t>0) {
            std::set<int> facs = primeFactors(j);
            if(facs.size()!=span)
                break;
            else 
                t--;

            j++;
        }
        if(t==0) {
            //print 1st and bail out
            std::cout << j-span << std::endl;
            return 0; 
        }
        i++;
    }
}

