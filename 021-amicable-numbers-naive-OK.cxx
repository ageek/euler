#include <iostream>
#include <vector> 

//Amicable numbers
//Problem 21
//
//Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
//If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.
//
//For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.
//
//Evaluate the sum of all the amicable numbers under 10000.
//
//I/O
//$echo "10000" | ./a.out
//

int getDivisors(int num) {
    std::vector<int> divs;

    for(int i=1; i<num; i++) {
        if(num%i == 0)
            divs.push_back(i);
    }
    //std::cout << num << ":";
    int sum=0;
    for(auto a: divs){
        //  std::cout << a << "  "; 
        sum += a;
    }
    //std::cout << ", sum=" << sum << std::endl;
    return sum;
}

int main() {
    int N;
    std::cin >> N;

    std::vector<int> amicables;

    for(int i=1; i<N; i++) {
        int x = getDivisors(i);
        int y = getDivisors(x);
        //avoid duplicates e.g.
        //d(6) = sum(1,2,3) =6
        //d(28) sum(1, 2, 4, 7, 14) = 28
        if(i==y && i!=x) {
            amicables.push_back(i);    
            amicables.push_back(x);
            //std::cout << i << " and  " << x << " are amicables " << std::endl; 
        }
    }

    int amicSum=0;
    for(auto a: amicables)
        amicSum += a;

    std::cout << amicSum << std::endl;
    return 0;
}

