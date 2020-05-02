#include <iostream>
#include <vector> 
#include <climits>

//Digit factorials
//Problem 34
//
//145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
//
//Find the sum of all numbers which are equal to the sum of the factorial of their digits.
//
//Note: as 1! = 1 and 2! = 2 are not sums they are not included.
//
//There is no 8-digit number which can be the sum of the factorials of its digits because `8 * 9! = 2903040` is a 7-digit number.
//
//I/O: ./a.out
//
int main() {
    
    // factorial chart for digits from 0 to 9
    int facChart[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
    int max = 8* facChart[9];

    int sum =0;
    for(int i=10; i<=max; i++) {
        int a=i;
        int facSum=0;
        while(a>0) {
            facSum += facChart[a%10];
            a /= 10;
        }
        if(i == facSum) {
            sum += i;
            //std::cout << i << std::endl;
        }
    }
    std::cout << sum << std::endl;

    return 0;
}

