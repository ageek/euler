#include <iostream>
#include <vector> 
#include <climits>
#include <cmath>

//Digit fifth powers
//Problem 30
//
//Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:
//
//    1634 = 1^4 + 6^4 + 3^4 + 4^4
//    8208 = 8^4 + 2^4 + 0^4 + 8^4
//    9474 = 9^4 + 4^4 + 7^4 + 4^4
//
//As 1 = 14 is not a sum it is not included.
//
//The sum of these numbers is 1634 + 8208 + 9474 = 19316.
//
//Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
//// # Algorithm
// The sum of the digits' fifth powers is maximized when each digit is 9:
// 1 digit:  `1 * 9^5 = 59049`
// 2 digits: `2 * 9^5 = 118098`
// 3 digits: `3 * 9^5 = 177147`
// 4 digits: `4 * 9^5 = 236196`
// 5 digits: `5 * 9^5 = 295245`
// 6 digits: `6 * 9^5 = 354294`
// 7 digits: `7 * 9^5 = 413343`
// //
// The last line is pretty interesting: it's impossible for a seven-digit number to have a seven-digit sum of its digits' fifth powers,
// because all those sums would have at most six digits.

// I/O:
// (base) topo@topobox:~/myRev/cpp/euler$ echo "4"|./a.out
//1634, 8208, 9474, 19316
//(base) topo@topobox:~/myRev/cpp/euler$ echo "5"|./a.out
//4150, 4151, 54748, 92727, 93084, 194979, 443839
//(base) topo@topobox:~/myRev/cpp/euler$
//

#define MAX 413343

int main() {

    int exp;
    std::cin >> exp;

    std::vector<int> nums;
    for(int i=2; i<=MAX; i++) {
        int n=i;
        int sum=0;
        while(n>0) {
            sum += pow(n%10,exp);
            n /=10;
        }
        if(i==sum){
            nums.push_back(i);
            }
    }
    int total=0;
    for(auto a: nums){
        std::cout << a << ", ";
        total += a;
    }
    std::cout << total << std::endl;
    return 0;
}
