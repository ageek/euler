#include <iostream>
#include <vector> 
#include <set>
#include <algorithm>
#include <climits>

//Prime pair sets
//Problem 60
//
//The primes 3, 7, 109, and 673, are quite remarkable. By taking any two primes and concatenating them in any order the result will always be prime. For example, taking 7 and 109, both 7109 and 1097 are prime. The sum of these four primes, 792, represents the lowest sum for a set of four primes with this property.
//
//Find the lowest sum for a set of five primes for which any two primes concatenate to produce another prime.
//
//Core algo: 
//1. find primes till some max, say 20k
//2. find set of bs for each a in primes[] such that ab, ba are both primes
//3. withing set of b's find c's such that bc and cb are both prime
//4  within set of bs find d's such that bd,db, cd, dc are all primes
//5. within set of b's find e's such that eb, be, de, ed, ce, ec are all primes
//
//Note: Faster primality test leads to a faster solution. Naive technique is very slow. On my 2GB Dual core VM, takes around 40s to spit out the min
//
//I/O:
//(base) topo@topobox:~/euler$ gpp -O3 060-Prime-pair-set-Naive-xtremely-slow-ok.cxx 
//(base) topo@topobox:~/euler$ time ./a.out 
//26033
//
//real	0m43.469s
//user	0m39.383s
//sys	0m0.067s
//(base) topo@topobox:~/euler$ 

//prime check: Naive and slow
bool isPrime(int num) {
    if(num==1)
        return false;

    bool isPrime=true;
    for(int i=2; i*i<=num; i++) {
        if(i*i>num)
            break;
        if(num % i==0) {
            isPrime = false;
            break;
        }
    }
    return isPrime;
}
// merge two numbers, "append their digits"
unsigned long long append(unsigned long long a, unsigned long long b)
{
    // append(34,56) -> 3456
    unsigned long long shift = 10;
    while (shift <= b)
        shift *= 10;
    return a * shift + b;
}

// check if ab and ba are both primes when appended together
bool isConcatPrime(unsigned long long a, unsigned long long b)
{
    return isPrime(append(a, b)) && isPrime(append(b, a));
}


int main() {
    int max=20000;
    std::vector<int> primes;
    primes.push_back(2);
    for(int i=3; i<=max; i+=2) {
        bool prime = true;
        for(auto p: primes) {
            if(p*p > i)
                break;
            if(i %p ==0) {
                prime=false;
                break;
            }
        }
        if(prime)
            primes.push_back(i);
    }

    //lambda expression to contcat two ints without using strings
    auto concat = [=](int a, int b)->int {
        int shift=10;
        while(shift <= b) 
            shift *= 10;
        return (a*shift + b);
    };

    int last=INT_MAX;
    //check all probales
    //we've to find 5 primes such that concat of any two is also a prime, and sum of all 5 primes is minimal
    for(int i=0; i<primes.size(); i++) {
        //for each primes[i], we've a set of probable elements that satisfy the property
        int first = primes[i];
        std::vector<int> probables;
        for(int index1=i+1; index1<primes.size(); index1++) {
            //index wise: 12 and 21 should be prime
            if(isConcatPrime(primes[i], primes[index1])) {
                probables.push_back(primes[index1]);
            } 
        }
        //std::cout << "for "<< primes[i] << " candidates are : ";
        //for(auto p: probables)
        //    std::cout << p << ",";
        //std::cout << std::endl;
        //
        //second prime can be any of the probables list
        //lets find the third: from probable list pick two which satisfies the property: both ab and ba primes
        for(int index2=0; index2<probables.size(); index2++) {
            for(int index3=index2+1; index3<probables.size(); index3++) {
                //found 3rd candidate
                //index wise: 23 and 32 should be prime
                if(isConcatPrime(probables[index2], probables[index3])) {
                    for(int index4=index3+1; index4<probables.size(); index4++) {
                        //found 4th candidate
                        //index wise: 24, 42 and 34, 43 should be prime
                        if(isConcatPrime(probables[index2], probables[index4]) && 
                                isConcatPrime(probables[index3], probables[index4])) {
                            for(int index5=index4+1; index5<probables.size(); index5++) {
                                //index wise: 25,52, 35,53, 45,54 should be prime
                                if(isConcatPrime(probables[index2], probables[index5]) &&
                                        isConcatPrime(probables[index3], probables[index5]) &&
                                        isConcatPrime(probables[index4], probables[index5])) {
                                    int sum = first + probables[index2] + probables[index3] + probables[index4] + probables[index5] ;
                                    //std::cout << "Found: " << first << "," << probables[index2] << ","<< probables[index3]  << ","<< probables[index4] 
                                    //    << "," << probables[index5]  << ",sum=" << sum << std::endl;
                                    if(last>sum)
                                        last = sum;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout << last << std::endl;
    return 0;
}

