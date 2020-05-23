#include <iostream>
#include <algorithm> 

//Lexicographic permutations
//Problem 24
//
//A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically, we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:
//
//012   021   102   120   201   210
//
//What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
//
//Use STL's std::next_permutation() to get the next lexicographic permutation...repeat 1000000 times
//
//
int main() {
    unsigned int permutationMax = 1000000;

    std::string base = "0123456789";
    while(--permutationMax) {
        std::next_permutation(base.begin(), base.end()) ;
    }
    std::cout << base << std::endl;

    return 0;
}

