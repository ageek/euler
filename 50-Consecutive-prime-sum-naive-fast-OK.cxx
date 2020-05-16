#include <iostream>
#include <vector> 
#include <algorithm>
#include <set>

//Consecutive prime sum
//Problem 50
//
//The prime 41, can be written as the sum of six consecutive primes:
//41 = 2 + 3 + 5 + 7 + 11 + 13
//
//This is the longest sum of consecutive primes that adds to a prime below one-hundred.
//
//The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.
//
//Which prime, below one-million, can be written as the sum of the most consecutive primes?
//
//core idea: 
//1. generate primes till max i.e. 10^6 :stored in vector
//2. generate cumulative sum from first to last element in above vector
//3. check if delta of cum sum array is max
//4. iterate over all delta's and save the max prime delta
//
//I/O:
//(base) topo@topobox:~/myRev/cpp/euler$ gpp -O3 Consecutive-prime-sum.cxx
//(base) topo@topobox:~/myRev/cpp/euler$ time echo 1000000|./a.out
//997651
//
//real	0m0.144s
//user	0m0.102s
//sys	0m0.000s
//(base) topo@topobox:~/myRev/cpp/euler$



int main() {

    // max as stated in Q=10^6
    int maxPrimes;
    std::cin >> maxPrimes;

    //precalculate primes upto max
    std::vector<int> primes;
    primes.push_back(2);
    for(int i=3; i<maxPrimes; i+=2) {
        bool isPrime=true;
        for(auto p: primes) {
            //p is too big a divisor for i
            if(p*p >i)
                break;
            if(i%p ==0){
                isPrime = false;
                break;
            }
        } 
        if(isPrime) 
            primes.push_back(i);
    }

    //    for(auto a: primes) 
    //        std::cout << a << ",";
    //    std::cout << std::endl;

    int maxValue = maxPrimes;

    //generate cumulative sum 
    std::vector<int> primeCumSum;
    int currentSum = primes[0];
    //to handle sum upto (including first element push 0 before pushing first primeSum)
    primeCumSum.push_back(0);
    primeCumSum.push_back(2);
    for(int i=1; i<primes.size(); i++) {
        currentSum += primes[i];
        if(currentSum >= maxValue)
            break;
        primeCumSum.push_back(currentSum);
    }
    //    for(auto a: primeCumSum) 
    //        std::cout << a << ",";
    //    std::cout << std::endl;

    //check for longest chain such that diff: primeCumSum[a] - primeCumSum[b] is also prime and a-b is maximized

    int maxA=0, maxB=0, chainSize=0;
    for(int a=primeCumSum.size()-1; a>=0; a--) {
        for(int b=0; b<primeCumSum.size(); b++) {
            if(std::binary_search(primes.begin(), primes.end(), primeCumSum[a] -primeCumSum[b]) && a > b) {
                // found max?
                if(a-b > chainSize) {
                    maxA = a;
                    maxB = b; 
                    chainSize = a-b;
                }
            }
        }
    }

    //    for(int x=maxB; x <maxA; x++) 
    //        std::cout << primes[x] << "," ;
    //    std::cout << std::endl << primeCumSum[maxA]  - primeCumSum[maxB] << " max chain len=" << chainSize << std::endl;
    std::cout << primeCumSum[maxA]  - primeCumSum[maxB] << std::endl;
    return 0;
}

