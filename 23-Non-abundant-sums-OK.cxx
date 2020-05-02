#include <iostream>
#include <algorithm>
#include <vector>
#include <set> 

//Non-abundant sums
//Problem 23
//
//A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.
//
//A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.
//
//As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.
//
//Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
//
//
//core algo:
//1. keep a growing list(abundants) abundant numbers till that number X
//2. check if X can be represented by sum of two abundant numbers < X
//loop over the vector of all abundants found so far: 
//  2a. if there exixts another abundant number (X-A) in the vector, skip X and check for X+1
//  2b. if loop is over, but no num found: this numbers need to be added up
//
//(base) topo@topobox:~/myRev/cpp/euler$ time echo 28213|./a.out
//4179871
//
//real	0m4.041s
//user	0m4.020s
//sys	0m0.001s
//(base) topo@topobox:~/myRev/cpp/euler
//
#define MAX 28123


// preprocess, find all abundant numbers till MAX 
std::set<int> abundants;
int max;

int sumDivisors(int num) {
    //start with default sum 1
    int sum=1;
    //std::cout << num << ":1," ; 
    for(int i=2; i*i <= num; i++) {
        if(num % i==0) {
            sum += i;
            //std::cout << i << ", ";
            int other = num/i;
            if(i != other) {
                sum += other;
                //std::cout << num/i << ", ";
            }
        }
    }
    //std::cout << ",sum=" << sum << std::endl;
    return sum;
}

bool isSummable(int x) {
    // check for first abundant num less than x
    for(auto a: abundants) {
        //this condition check speeds up time by 3X
        if (a >= x)
            return false;

        // find such an 'a' for which x-a + a =x, i.e. x is summable
        // if we are through the abundants set and still nto able to find 
        // then its not
        if ((abundants.count(x-a) == 0)) {
            //std::cout << "Summable :" << a << "+" << (x-a) << "=" << x <<  std::endl;
            continue;
        } 
        // else, we dont have any a, for which x-a is E {abundants}
        //std::cout << x << " is summable: " << a << "+" << x-a << std::endl;
        return true;
    }
    //thru loop, but not found any a, for which a+x-a is summable
    //otherwise
    return false;
}

int main() {
    std::cin >> max;

    for(int i=1; i<=max; i++)
        sumDivisors(i);

      for(int i=1; i<= max; i++) {
          if( i < sumDivisors(i) )
              abundants.insert(i);
      }

    //      for(auto a: abundants)
    //          std::cout << a << "  "; 

    //  // sum of numbers that can't be represented as sum of two Abundant nums
    int result =0;
      for(int i=1; i<=max; i++) {
          if(!isSummable(i)) {
              result += i;
          }
      }
    std::cout << result << std::endl;

    return 0;
}

