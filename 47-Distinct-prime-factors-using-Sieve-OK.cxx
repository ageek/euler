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

int main() {
    int span =4;
    int max=500000+span-1;

    //vector for all nums where the  value represents:no of prime factors;
    //default fac count for all to 0
    std::vector<int> facCount(max,0);
    for(int i=2; i<=max; i++) {
      if(facCount[i]==0) {
        // Use sieve technique to mark multiples (here we increment counter instead of marking out)
        //all multiples of i (hence x += i) will have their fac coutn value incremented by i
        for(int x=i; x<=max; x +=i ) {
            facCount[x]++;
        }
      }  
    }
    //iterate over the facCount vector and print first with 4 consecutive no with faccount 4
    for(int i=2; i<= max; i++) {
        if( facCount[i]==span && 
                facCount[i+1]==span &&
                facCount[i+2]==span &&
                facCount[i+3]==span) {
            std::cout << i << std::endl;
            //found one, bail out
            return 0;
        }

    }
}

