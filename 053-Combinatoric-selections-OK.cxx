#include <iostream>
#include <vector> 
#include <set>
#include <algorithm>

//Combinatoric selections
//Problem 53
//
//There are exactly ten ways of selecting three from five, 12345:
//123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
//In combinatorics, we use the notation, C(5,3)=10
//
//In general, C(n,r)=n!r!/(n−r)!  where r≤n, n!=n×(n−1)×...×3×2×1, and 0!=1
//
//It is not until n=23  that a value exceeds one-million: C(23,10)=1144066
//
//How many, not necessarily distinct, values of C(n,r) for 1≤n≤100, are greater than one-million?
//
//Core algo:
//1.C(n,0)= C(n,n)=1
//2.recursively calculate C(n,r)=C(n-1,r)+ C(n-1, r-1)
//3.any value > BIG should be marked as BIG and count incremented (count is the count of how many values are greater than BIG)
//I/O: 
//(base) topo@topobox:~/myRev/cpp/euler$ time ./a.out 
//4075
//
//real	0m0.003s
//user	0m0.000s
//sys	0m0.002s
//(base) topo@topobox:~/myRev/cpp/euler$
//



int main() {
    // max n/r values 
    int N = 100;

    // max value = 10^6 , as stated
    unsigned int BIG = 1000000;

    //cache
    //for storing previously calculated values 
    //for N=0 to N
    std::vector<std::vector<unsigned long>> combinations(N+1);

    // fill the base values and resize internal sub-vectors to size N+1
    // C(n,0)= C(n,n)=1
    for(int n=0; n<=N; n++) {
        //resize each sub-vector to size N+1 and set default value to 0
        combinations[n].resize(N+1, 0);
        combinations[n][0]=1;
        combinations[n][n]=1;
    }
    //recursively calculate C(n,r) using C(n-1,r) & C(n-1, r-1)
    int count = 0;
    for(int n=1; n<=N; n++) {
        for(int r=1; r<=n; r++) {
            //C(n,r) = C(n-1, r) + C(n-1, r-1)
            auto result = combinations[n-1][r] + combinations[n-1][r-1] ;
            if (result > BIG) {
                result = BIG ; 
                count++;
            }
            combinations[n][r] = result;
        }
    }

    std::cout << count << std::endl;
    return 0;
}

