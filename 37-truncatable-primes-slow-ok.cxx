#include <iostream>
#include <vector> 
#include <cmath>
//
//Truncatable primes
//Problem 37
//
//The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.
//
//Find the sum of the only eleven primes that are both truncatable from left to right and right to left.
//
//NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
//
//
bool isPrime(int  n) {
    if(n <= 1)
        return false;

    for(int i=2; i*i <= n; i++) {
        if(n % i ==0 )
            return false;
    }
    //    std::cout << n << " is prime " << std::endl;
    return true;
}

int rev(int num) {
    int rev = 0;
    int t = num;
    while(t > 0) {
        rev = t%10 + rev * 10;
        t /= 10;
    }
    return rev;
}

//this check if x is truncatable
bool isTruncatable(int x) {
    bool result = true;
    //check right/left truncatables are prime or not?
    //i.e.we can work from right to left: 3797, 379, 37, and 3.
    int rtol = x;
    while(rtol > 0) {
        //if one failed, we bail out and check next i
        if(!isPrime(rtol)) {
            result = false;
            break;
        }
        rtol /= 10;
    }
    if (result) {
        std::cout << x << " is truncatable" << std::endl;
    }
    return result;
}

int main() {

    // max can be 9 digits?
    int max;
    std::cin >> max; 

    //precalculate all primes till max;
    std::vector<int> primes;
    primes.push_back(2);
    primes.push_back(3);
    primes.push_back(5);
    primes.push_back(7);
    //check for odd nums only
    for(int i=11; i<max; i +=2) {
        bool res = true;
        for(int x=i; x*x <=i ; x++) {
            if(i %x == 0 )
                res = false;
        }
        if(res)
            primes.push_back(i);
    }
    //    for(auto a: primes)
    //        std::cout << a << ","; 
    //    std::cout << std::endl;

    //
    //    isTruncatable(379);
    //    isTruncatable(rev(973));

    //start with 2 digits
    //start with odd and up by 2
    int sum = 0;
    for(int i=11; i<=max; i += 2){

        //check if i is prime
        if(isPrime(i)) {
            //check right truncatables are prime or not?
            //i.e.we can work from right to left: 3797, 379, 37, and 3.
            //right to left
            int rtol = i/10;
            bool left = true;
            while(rtol > 0) {
                //remove right most digit
                if(!isPrime(rtol)) {
                    left = false;
                    break;
                }
                rtol /= 10;
            }
            //if one failed, we bail out and check next i
            if (!left) {
                continue;
            }
            //    std::cout << i << " is right truncatable" << std::endl;
            //else
            //check for left truncatables
            // 377 -> 77 - > 7  
            //left to right
            int ltor = i;
            bool right = true;
            int d = std::to_string(i).length();
            while(d-- > 0) {
                //remove left most digit
                if(!isPrime(ltor)) {
                    right = false;
                    break;
                }
                ltor  %= (int)(pow(10, d));
            }
            if(!right) {
                continue;
            }
            //    std::cout << i << " is left truncatable" << std::endl;
            //else i is both left and right truncatable

            if(right && left) {
                //std::cout << i << " is both ways truncatable " << std::endl;
                std::cout << i << std::endl;
                sum += i;
            }
        }
    }
    std::cout << sum << std::endl;

    return 0;
}

