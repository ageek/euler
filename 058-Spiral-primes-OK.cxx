#include <iostream>
#include <vector> 
#include <set> 

//Spiral primes
//Problem 58
//
//Starting with 1 and spiralling anticlockwise in the following way, a square spiral with side length 7 is formed.
//
//37 36 35 34 33 32 31
//38 17 16 15 14 13 30
//39 18  5  4  3 12 29
//40 19  6  1  2 11 28
//41 20  7  8  9 10 27
//42 21 22 23 24 25 26
//43 44 45 46 47 48 49
//
//It is interesting to note that the odd squares lie along the bottom right diagonal, but what is more interesting is that 8 out of the 13 numbers lying along both diagonals are prime; that is, a ratio of 8/13 ≈ 62%.
//
//If one complete new layer is wrapped around the spiral above, a square spiral with side length 9 will be formed. If this process is continued, what is the side length of the square spiral for which the ratio of primes along both diagonals first falls below 10%?
//
//Refer Prob 28 (clockwise spiral problem) for details:
//core algo for Prob 58: 
//1. base =1 for layer/level =1 (the innnermost element)
//2. layer=2 onwards, we need to find the first element(dependent on the last element of last layer) and the remaining
//   3 are equidistant, delta  of which is dependent on the layer no
//3. for each layer, find the 1st, 1st+delta, 1st+2*delta, 1st+3*delta and keep track of how many diagonal elements are prime
//4. loop till prime ration < 10%, print layer
//
//Note: 1.ratio is around 13% till layer 1113 and with 5 million primes. Faster approach would be to test primality of corner elements instread of generating 
//      5 million + primes
//      2. a faster primality testing algo will lead to an efficient solution. 
//      3. One option would be to use Miller Rabin Test: https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test 
//      4. Naive primality testing is decently fast. On my 2GB RAM, 1CPU VM it takes <1.5s to spit out the answer
//I/O: 
//(base) topo@topobox:~/myRev/cpp/euler$ gpp -O3 058-Spiral-primes.cxx
//(base) topo@topobox:~/myRev/cpp/euler$ time ./a.out
//26241
//real	0m1.350s
//user	0m1.271s
//sys	0m0.000s
//(base) topo@topobox:~/myRev/cpp/euler$ 

//Primality testing
//A faster primatlity check => efficient solution
bool isPrime(unsigned long num) {
    //adds a little bit of speedup
    if(num%2 == 0)
        return false;

    bool isPrime = true;
    for(int i=2; i*i <=num; i++) {
        if(num %i ==0) {
            isPrime = false;
            break;
        }
    }
    return isPrime;
}

int main() {
    // base layer 
    int layer =1;
    // base element of spiral path
    int last  =1;
    //track %
    int primeCount = 0;
    int totalCount = 1; //base layer, afterwards each layer adds 4 new diagonal elements 

    while(true) {
        layer++;
        //to add 4 elements
        int n=4;
        //total no of elements till this layer
        totalCount += n;
        //delta between each corner elements
        int delta = 2*(layer-1);

        while(n-- > 0) {
            int current = delta + last;
            //check primality
            if(isPrime(current)) 
                primeCount++;
            //save last 
            last = current;
        }
        //check ratio
        auto ratio = 100* ((float)primeCount/(float)totalCount);
        //std::cout << ",layer=" << layer << ",primeCount=" << primeCount << ", totalCount=" << totalCount << ",ratio=" << ratio << std::endl;
        if(ratio < 10){
            //side length is dependent on layer no: lenght = 2*layer-1
            std::cout << 2*layer-1;
            break;
        }
    }
    return 0;
}

