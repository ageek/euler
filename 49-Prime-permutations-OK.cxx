#include <iostream>
#include <vector> 
#include <algorithm>
#include <numeric>

//Prime permutations
//Show HTML problem content
//Problem 49
//
//The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, is unusual in two ways: (i) each of the three terms are prime, and, (ii) each of the 4-digit numbers are permutations of one another.
//
//There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property, but there is one other 4-digit increasing sequence.
//
//What 12-digit number do you form by concatenating the three terms in this sequence?
//
//core algo:
//Note: Problem doesn't ask for Pandigital numbers, just any 4-digit number sequence
//step1: for each of 1000 to 9999
//step2: generate all permutations and check the given condition

//use lambda expression instead
int sumUp(int a, int b) {
    return (10*a + b) ;
}

int main() {
    int max=9999;
    //precaculate all primes till 9999
    std::vector<int> primes;
    //base element
    primes.push_back(2);
    for(int i=3; i<=max; i+=2) {
        bool isPrime=true;
        for(auto a: primes) {
            if(a*a >i) 
                break;
            if(i%a==0) {
                isPrime = false;
                break;
            }
        }
        if(isPrime)
            primes.push_back(i);
    }

    //to speed up overall lookup, could do wihtout seen, but that would be a bit inefficient
    std::vector<bool> seen(10000,false);
    
    //check for all possible 4-digit numbers (need not be a pan digital)
    for(int i=1000; i<10000; i++) {
        //convert num to vector
        // 2345 -> {2,3,4,5}
        std::vector<int> a(4);
        for(int j=0, t=i; j<4; j++ ) {
            a[3-j]= t%10;
            t /= 10;
        }

        //generate all permutatiions of this number and check
        std::vector<int> permutations;
        do {
            //int current = std::accumulate(a.begin(), a.end(),0, sumUp);
            //
            // used lambda expression to calculate curernt value to accumulate
            int current = std::accumulate(a.begin(), a.end(),0, [&](int x, int y){return 10*x+y;});
            //this is a new prime number not seen earlier, save it
            if(!seen[current] && std::binary_search(primes.begin(), primes.end(), current)) {
                seen[current] = true;
                permutations.push_back(current);
            }
        }while(std::next_permutation(a.begin(), a.end()));

        //step throug all the values in permutations and see if any triplet satisfies the condition
        //permutations are in increaseing order of value so we should check for delta: y-x == z-y
        for(int x=0; x< permutations.size(); x++) {
            for(int y=x+1; y<permutations.size(); y++) {
                for(int z=y+1; z<permutations.size(); z++) {
                    //skipe 1487
                    if(permutations[x] !=1487 && permutations[y]-permutations[x] == permutations[z]-permutations[y]) {
                        //found one, print and quit
                        std::cout << permutations[x] << permutations[y] << permutations[z] << std::endl;
                        return 0;
                    }
                }
            }
        }
        
    }

    return 0;
}

