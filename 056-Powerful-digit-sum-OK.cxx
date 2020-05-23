#include <iostream>
#include <vector> 
#include <set>
#include <algorithm>

//Powerful digit sum
//Problem 56
//
//A googol (10100) is a massive number: one followed by one-hundred zeros; 100^100 is almost unimaginably large: one followed by two-hundred zeros. Despite their size, the sum of the digits in each number is only 1.
//
//Considering natural numbers of the form, ab, where a, b < 100, what is the maximum digital sum?
//
//core algo:
//1. convert num to vector format and multiply vec with int in a loop
//2. keep track of max sum
//3. overload * for vec * int
//
//I/O:
//(base) topo@topobox:~/myRev/cpp/euler$ gpp -O3 Powerful-digit-sum.cxx
//(base) topo@topobox:~/myRev/cpp/euler$ time ./a.out
//972
//
//real	0m0.041s
//user	0m0.016s
//sys	0m0.004s
//(base) topo@topobox:~/myRev/cpp/euler$

//overload * for std::vector<int> * int
std::vector<int> operator*(std::vector<int> number, int exp) {
    //numbers are represented as 
    // 2345 -> {5, 4, 3, 2} in vector form (LSB first)

    //multiply with exp
    std::vector<int> prod;
    int carry = 0; 
    for(auto a: number) {
        int result = carry + exp * a;
        //check carry
        carry = result/10;
        result = result % 10;
        prod.push_back(result);
    }
    //loop  over but still carry >0 
    //carry may be 2 or 3 digit, loop and push all with %10
    while(carry>0) {
        prod.push_back(carry%10);
        carry /= 10;
    }
    return prod;
}

int main() {
    int max = 100;

    //lambda expression for number to vector conversion
    //2345 - > {5,4,3,2}
    auto num2vec = [](int x)->std::vector<int> {
        std::vector<int> vec;
        do {
            vec.push_back(x%10);
            x /= 10;
        } while(x>0);

        return vec;
    };

    int maxSum = 0;
    int maxBase = 0;
    int maxExp = 0;
    // base 
    for(int a=1; a<=max; a++) {
        //exponent
        std::vector<int> current = num2vec(1);
        for(int b=1; b<=max; b++) {
            //multiply a , b times i.e. a*a*a ....b times in this loop
            current = current * a;

            int sum=0;
            for(auto d: current)
                sum += d;

            if(maxSum < sum) {
                maxSum = sum;
                maxBase = a;
                maxExp = b;
            }
        }
    }

    //std::cout << maxBase << "^" << maxExp << ", sum of digs=" << maxSum << std::endl;
    std::cout << maxSum << std::endl;
    return 0;
}

