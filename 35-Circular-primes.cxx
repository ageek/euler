#include <iostream>
#include <vector> 
#include <cmath>

//Circular primes
//Problem 35
//
//The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.
//
//There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
//
//How many circular primes are there below one million?
//
//
//I/O:
//(base) topo@topobox:~/euler$ echo "1000000"|./a.out
//55
//(base) topo@topobox:~/euler$

bool isPrime(int n) {
    for(int i=2; i *i <= n; i++) {
        if(n % i == 0)
            return false;
    }

    //std::cout << n << " is prime " << std::endl;
    return true;
}

int main() {
    //here its 10^6 = 1000,000
    int limit ;
    std::cin >> limit;

    std::vector<int> primeRots;
    // add base num 2
    primeRots.push_back(2);
    //from 1 to 10^6, check each and all its rotations are prime or not?
    for(int i=3; i<limit; i +=2) {
        // check if i is prime, if yes check its rotations are prime?
        if(isPrime(i)) {
            //no of rotations for i = length(i)-1
            //need to check for digits >=2
            if(i<10) {
                primeRots.push_back(i);
                continue;
            }
            int d=0;
            int t=i;
            while(t>0) {
                d++;
                t /= 10;
            }
            // total number of rotations excluding the base number i
            int rotationCount= d-1;
            //check if all rotations are prime, 
            bool all = true;
            int current = i;
            while(rotationCount-- >0) {
                //get next cycic rotation of i
                // 197 -> 719 -> 971 -> 179
                //int x = current %10;
                //int rem = current /10;
                //int rotation = x*pow(10,d-1) + rem;
                //
                int nextRotation = (current %10) * pow(10,d-1) + (current / 10);
                if(!isPrime(nextRotation)){
                    all = false;
                    //found one failing condition, skip this i
                    break;
                }
                //save this rotation for next iteration
                current  = nextRotation;
            }
            // we are thru the loop, and none failed prime check
            // add this to our list
            if (all == true) {
                primeRots.push_back(i);
            }
        }

    }

//    for(auto a: primeRots)
//        std::cout << a << ",";
    std::cout << primeRots.size() << std::endl;
    return 0;
}

