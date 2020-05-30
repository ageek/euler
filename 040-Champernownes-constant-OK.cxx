#include <iostream>
#include <vector> 
//
//Champernowne's constant
//Problem 40
//
//An irrational decimal fraction is created by concatenating the positive integers:
//
//0.123456789101112131415161718192021...
//
//It can be seen that the 12th digit of the fractional part is 1.
//
//If dn represents the nth digit of the fractional part, find the value of the following expression.
//
//d1 × d10 × d100 × d1000 × d10000 × d100000 × d1000000
//
//core idea:
//1. we need to concatenate 1,2,3 .....10^6 and store in string and pick the required chars convert to int and multiply
//
//Note: this basic approach is fast enough, and there is no need for optimization
//
//I/O:
//(base) topo@topobox:~/myRev/cpp/euler$ time echo 1000000|./a.out
//210
//
//real	0m0.538s
//user	0m0.526s
//sys	0m0.004s
//(base) topo@topobox:~/myRev/cpp/euler$

int main() {
    //here max=10^6
    int max; 
    std::cin >> max; 

    std::string N="";
    for(int i=1; i<= max; i++) {
        N += std::to_string(i);
    }
    //now pick the stored chars and multiply
    int d=1;
    int res=1;
    while(d <= max) {
        //arry index is from 0 onwards, which should be 1 onwards 
        //std::cout << "d:" << d << ", " << N[d-1]-'0' << std::endl;
        res *= N[d-1] - '0';
        d *= 10;
    }
    //std::cout << N << std::endl;
    std::cout << res << std::endl;


    return 0;
}

