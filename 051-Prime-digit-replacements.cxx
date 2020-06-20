#include <iostream>
#include <string>
#include <vector> 
#include <set>
#include <algorithm>
#include <cmath>

//Prime digit replacements
//Problem 51
//
//By replacing the 1st digit of the 2-digit number *3, it turns out that six of the nine possible values: 13, 23, 43, 53, 73, and 83, are all prime.
//
//By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit number is the first example having seven primes among the ten generated numbers, yielding the family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993. Consequently 56003, being the first member of this family, is the smallest prime with this property.
//
//Find the smallest prime which, by replacing part of the number (not necessarily adjacent digits) with the same digit, is part of an eight prime value family.
//
//core algo:
//1. generete all primes till some max (say 6 dig max:999999)
//2. for each x-dig set of primes
//2a. check if the signature indicates a digit occuring >=2 times 
//2b. if yes, check all possible replaces of the digit that occurs >=2 times
//2c. keep a count, if count >=8 print and quit
//
//I/O:
//(base) topo@topobox:~/myRev/cpp/euler$ gpp -O3 051-Prime-digit-replacements.cxx
//(base) topo@topobox:~/myRev/cpp/euler$ time ./a.out
//121313
//
//real	0m0.474s
//user	0m0.432s
//sys	0m0.004s
//(base) topo@topobox:~/myRev/cpp/euler$
//Note: - Efficient primality testing techniques e.g. Miller-Rabin can be used to speed up the work
//      - Current code is decently fast on my 2GB RAM dual core Ubuntu VM, so not doing any speed up enhancements for now


// convert num to signature i.e. occurence count of each digit from 0 to 9 
// placed at corresponding index value
// e.g. 66458 ->0000112010
std::string signature(int num) {
    std::string result ("0000000000");
    while(num>0) {
        int t = num %10;
        result[t] = result[t] + 1 ;
        num /= 10;
    }
    return result;
}


int main() {
    // looking for how many primes out of 10?
    int maxPrimeFamilySize = 8; 

    std::set<int> primes;
    //Example query is 5 dig,
    //Expected asnwer will have >=5 digs
    int maxPrime = 999999;
    primes.insert(2);

    //master replacements list
    std::set<int> masterList;

    // gather all primes till max
    for(int i=3; i<=maxPrime; i++) {
        bool isPrime = true;
        for(auto p: primes) {
            if(p*p > i)
                break;
            if(i%p == 0) {
                isPrime = false;
                break;
            }
        }
        if(isPrime)
            primes.insert(i);
    }
    
    //lambda expression to replace all x by y 
    auto replace=[](int num, int x, int y)->int {
        int current=0, t=0;
        while(num>0) {
            int p=num%10;
            if(p==x)
                p=y;
            current += pow(10,t)*p;
            t++;
            num /= 10;
        }
        return current;
    };

    // check for 5, 6 digit primes only
    for(int i=5; i<7; i++) {
        //new masterist for each n-digit set
        masterList.clear();
        int min = pow(10, i-1);
        int max = pow(10, i) -1;

        //From the list of primes, pick only the ones belowing to this range
        auto lb = std::lower_bound(primes.begin(), primes.end(), min);
        auto ub = std::upper_bound(primes.begin(), primes.end(), max);

        //std::cout << "for i " << i << " digits: " << std::endl;
        for(auto x=lb; x!=ub; x++) {
            //have we seen this replacement earlier? 
            //i.e.56003 can appear multiple times, every time one of its replacements appears
            if(masterList.count(*x)!=0)
                continue;
            //else add it
            masterList.insert(*x);

            auto sig = signature(*x); 
            //which digits occur more than once? 
            for(int j=0; j<=sig.size(); j++) {
                //convert char to ascii for comparison
                if(sig[j] -'0' >=2) {
                    auto dig = j;
                    std::set<int> repSet;
                    //add the base element
                    repSet.insert(*x);
                    // check all replacements of dig by 0 to 9 (except dig) and check 
                    // if the corresponding number is prime? total count > maxPrimeFamilySize?
                    int current = 0;
                    for(int z=0; z<10 ; z++) {
                        if(z==dig)
                            continue;
                       current = replace(*x, dig, z);
                       //numbers with 0 MSB need to be skipped i.e. 007, 0987 etc
                       if(current < *lb)
                           continue;
                       //is replaced num a prime?
                       if(primes.count(current)!=0) {
                            repSet.insert(current);
                            //this needs to be inserted to masterList as well
                            masterList.insert(current);
                       }
                    }
                    if(repSet.size()>= maxPrimeFamilySize) {
                        std::cout << *std::min_element(repSet.begin(), repSet.end()) << std::endl;
                        return 0;
                    }
                }
            }

        }
    }
    return 0;
}

