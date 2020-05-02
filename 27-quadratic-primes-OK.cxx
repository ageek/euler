#include <iostream>
#include <vector> 
#include <set> 

//Euler discovered the remarkable quadratic formula:
//
//n2+n+41
//
//It turns out that the formula will produce 40 primes for the consecutive integer values 0≤n≤39
//. However, when n=40,40^2+40+41=40(40+1)+41 is divisible by 41, and certainly when n=41,412+41+41
//
//is clearly divisible by 41.
//
//The incredible formula n^2−79n+1601
//was discovered, which produces 80 primes for the consecutive values 0≤n≤79
//
//. The product of the coefficients, −79 and 1601, is −126479.
//
//Considering quadratics of the form:
//
//    n^2+an+b
//
//, where |a|<1000 and |b|≤1000
//
//where |n|
//is the modulus/absolute value of n
//e.g. |11|=11 and |−4|=4
//
//Find the product of the coefficients, a
//and b, for the quadratic expression that produces the maximum number of primes for consecutive values of n, starting with n=0.
//
std::set<int> primes;

//when prime checking is done sequentially, this is oka
//not used for this problem
bool isPrime(int x) {
    for(auto a: primes) {
        if(x % a == 0)
            return false;
    }
    //add x to primes
    primes.insert(x);
    std::cout << x << " is prime " << std::endl;
    return true;

}

// for random prime check, we've to check all divisors
bool isPrimeNum(int x) {
    if(x<=1)
        return false;
    
    for(int i=2; i*i <=x; i++) {
        if(x % i ==0 ) 
            return false;
    }
    //std::cout << x << " is prime " << std::endl;
    return true;
}
int main() {
    int aLimit, bLimit;
    std::cin >>aLimit >> bLimit;

    int bestA;
    int bestB;
    int bestChainLength=0;
    // |a| < 1000
    // |b| <= 1000

    for(int a=-aLimit+1; a < aLimit; a++) {
        for(int b=-bLimit; b <= bLimit; b++) {
            // for n=0 onwards
            int n=0;
            while(isPrimeNum(n*n + a*n + b)) 
                n++; 
            if( bestChainLength < n) {
                bestChainLength = n;
                bestA = a;
                bestB = b;
            }
            //std::cout << "a=" << a << ",b=" << b << " has max prime chain lenght= "<< n << std::endl;
        }
    }
            //std::cout << "a=" << bestA << ",b=" << bestB << " has max prime chain lenght= "<< bestChainLength << std::endl;
            std::cout << bestA * bestB << std::endl;
    return 0;
}

