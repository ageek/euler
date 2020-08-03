#include <iostream>
#include <vector> 
#include <set>
#include <algorithm>

//Ordered fractions
//Problem 71
//
//Consider the fraction, n/d, where n and d are positive integers. If n<d and HCF(n,d)=1, it is called a reduced proper fraction.
//
//If we list the set of reduced proper fractions for d ≤ 8 in ascending order of size, we get:
//
//1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
//
//It can be seen that 2/5 is the fraction immediately to the left of 3/7.
//
//By listing the set of reduced proper fractions for d ≤ 1,000,000 in ascending order of size, find the numerator of the fraction immediately to the left of 3/7.
//
//I/O:
//(base) topo@topobox:~/myRev/cpp/euler$ gpp -O3 071-Ordered-Fractions.cxx
//(base) topo@topobox:~/myRev/cpp/euler$
//(base) topo@topobox:~/myRev/cpp/euler$ time echo "8"|./a.out 
//2/5
//
//real	0m0.005s
//user	0m0.001s
//sys	0m0.003s
//(base) topo@topobox:~/myRev/cpp/euler$ time echo "1000"|./a.out 
//428/999
//
//real	0m0.004s
//user	0m0.003s
//sys	0m0.000s
//(base) topo@topobox:~/myRev/cpp/euler$ time echo "1000000"|./a.out 
//428570/999997
//
//real	0m0.004s
//user	0m0.001s
//sys	0m0.003s
//(base) topo@topobox:~/myRev/cpp/euler$ 
// mediant of a/b & c/d = (a+c)/(b+d); 
// check details here: 
// https://en.wikipedia.org/wiki/Stern%E2%80%93Brocot_tree
// https://en.wikipedia.org/wiki/Farey_sequence


int main() {
    //max denominator allowed : d ≤ 1,000,000
    unsigned int dMax ;
    std::cin >> dMax; 

    //left of which element?
    unsigned int a = 3;
    unsigned int b = 7; 

    //start with base case, where we have 0/1 and 1/1 and two elements and we need to find the mediant using Farey's sequence
    // mediant of a/b & c/d = (a+c)/(b+d); 
    // check details here: 
    // https://en.wikipedia.org/wiki/Stern%E2%80%93Brocot_tree
    // https://en.wikipedia.org/wiki/Farey_sequence
    unsigned long long leftN = 0;
    unsigned long long leftD = 1; 
    unsigned long long rightN = 1;
    unsigned long long rightD = 1; 

    //continue till the mediant denominator <= dMax i.e. 10^6
    while(leftD + rightD <= dMax) {
        auto mediantN = leftN + rightN;
        auto mediantD = leftD + rightD;
        // check where the mediant lies, i.e. left of 3/7 or right of 3/7 and adjust the next two elements accordingly
        //
        // p/q < r/s if p*s < q*r
        // ratio is less than a/b, then we need to use mediant for calculating the next ratio
        if((unsigned __int128) mediantN * b < (unsigned __int128)mediantD * a) {
            leftN = mediantN;
            leftD = mediantD; 
        } else {
            rightN = mediantN;
            rightD = mediantD;
            if(rightN==a && rightD==b)
                break;
        }
    }
    while (leftD + rightD <= dMax) // gets the job done, but still slow ...
    {
        leftN += rightN;
        leftD += rightD;
    }

    std::cout << leftN << "/" << leftD << std::endl;

    return 0;
}

