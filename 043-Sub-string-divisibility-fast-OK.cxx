#include <iostream>
#include <vector> 
#include <set>
#include <algorithm>

//Sub-string divisibility
//Problem 43
//
//The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order, but it also has a rather interesting sub-string divisibility property.
//
//Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:
//
//    d2d3d4=406 is divisible by 2
//    d3d4d5=063 is divisible by 3
//    d4d5d6=635 is divisible by 5
//    d5d6d7=357 is divisible by 7
//    d6d7d8=572 is divisible by 11
//    d7d8d9=728 is divisible by 13
//    d8d9d10=289 is divisible by 17
//
//Find the sum of all 0 to 9 pandigital numbers with this property.
//
//algo:
//1. get all permutations of the given set of digits 
//2. check divisibility by the list of primes
//I/O:
//(base) topo@topobox:~/myRev/cpp/euler$ time ./a.out
//16695334890
//
//real	0m2.888s
//user	0m2.837s
//sys	0m0.000s
//(base) topo@topobox:~/myRev/cpp/euler$

//Not used
//just method invocation adds around 50% overhead
bool isPanDivisible(std::string x) {
    std::vector<int> divs={2,3,5,7,11,13,17};
    int span=3;
    int pos =1;
    while(pos < 8 ) {
        long num = std::stol(x.substr(pos, span));
        //if one fails divisibility check, bail out
        if(num % divs[pos-1] !=0 )
            return false;
        pos++;
    }
    return true;
}

int main() {
    //primes to divide by
    std::vector<int> divs={2,3,5,7,11,13,17};

    long sum = 0;
    std::string str = "0123456789";
    std::set<std::string> pandigitals;

    //iterate over all the permutations of str and check for divisibility
    do {
        int pos=1;
        bool isPan = true;
        while(pos < 8 ) {
            long num = std::stol(str.substr(pos, 3));
            //if one fails divisibility check, bail out
            if(num % divs[pos-1] !=0 ) {
                isPan = false;
                break;
            }
            pos++;
        }
        if(isPan){
        //calling the method isPanDiv...() instead doing it locally adds ~2sec overhead for total time of ~4s
        //i.e. method invocation is ~50% overhead !!!
        //if(isPanDivisible(str)){
            sum += std::stol(str);
        }

    }while(std::next_permutation(str.begin(), str.end()));
    std::cout << sum << std::endl;

    return 0;
}

