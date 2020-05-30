#include <iostream>
#include <vector> 
#include <set>
#include <algorithm>

//Pandigital products
//Problem 32
//
//We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.
//
//The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.
//
//Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.
//HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.
//
//core algo: 
//1. max permutations of n digits is n!
//2. use std::next_permutation(vec of 9 digits) to generate next permutation
//3. loop and check all possible combination of lenghts and see if a*b =c
//4. sum up when a*b=c

int main() {


    std::vector<int> allowed = {1,2,3,4,5,6,7,8,9};
    std::set<int> panDigits;
    int max = allowed.size();

    //std::next_permutation(begin, end);
    //Return value
    //true  : if the new permutation is lexicographically greater than the old. 
    //false : if the last permutation was reached and the range was reset to the first permutation.
    while(std::next_permutation(allowed.begin(), allowed.end())) {
        //for each permutation of allowed, form a , b and check a*b =c
        for(int lenA=1; lenA < max; lenA++ ) {
            for(int lenB=1; lenB <max-lenA; lenB++) {
                int lenC = max - lenA - lenB;
                // removes spurious checks
                // a*b=c => c>=a && c>=b => c has at least as many digits as a or b
                if (lenC < lenA || lenC < lenB)
                    break;

                int p=0;
                //make a
                int a =0;
                for(int i=1; i<=lenA; i++) {
                    a *=10;
                    a += allowed[p++];
                }

                //make b
                int b=0;
                for(int j=1; j<=lenB; j++) {
                    b *=10;
                    b += allowed[p++];
                }

                //make c
                int c=0;
                for(int k=1; k<=lenC; k++) {
                    c *=10;
                    c += allowed[p++];
                }

                //check if a*b =c
                if(a *b == c) {
                    panDigits.insert(c);
                    //std::cout << a << "*" << b << "=" << c << std::endl;
                }
            }
        }

    }
    int sum = 0;
    for(auto a: panDigits){
        sum += a;
    }

    std::cout << sum << std::endl;
    return 0;
}

