#include <iostream>
#include <vector> 
#include <set>
#include <algorithm>
#include <numeric>
#include <string> // for stoi


//Permuted multiples
//Problem 52
//
//It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different order.
//
//Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.
//
//core algo:
//1.convert number to its signature [signature is 10 char string array where index value corresponds to presence/count of that index's appearance in number]
//2.possible candidates are 6 digit numbers starting with 1 
//3.generate all C(9,6) combinations and save all starting with 1 as candidate
//4.for each candidate generate all permutations and check condition of x=2x, x=3x ...x=6x;
//
//I/O:
//(base) topo@topobox:~/myRev/cpp/euler$ time ./a.out
//142857
//
//real	0m0.004s
//user	0m0.003s
//sys	0m0.000s
//(base) topo@topobox:~/myRev/cpp/euler$




//Convert number to signature
//2345 -> 0011110000
//2234 -> 0021100000
std::string signature(int num) {
    std::string sig ("0000000000");
    while(num > 0) {
        int t= num %10;

        sig[t]=sig[t]+1+'0';
        num /= 10;
    }
    return sig;
}

int main() {
    // num has to be 6 digits
    // first digit must be 1, remaing can be from 2 to 9
    std::vector<bool> num(9, false) ;
    std::fill(num.end()-6, num.end(), true);

    //a sorted set of all candidate number
    std::set<int> candidates;

    //generate all candidate elements
    do {
        std::string current ="";
        for(int i=0; i<num.size(); i++) {
            if(num[i])
                current += std::to_string(i+1);
        }
        //must start with 1
        if(current[0]=='1')
            candidates.insert(std::stoi(current));
    } while(std::next_permutation(num.begin(), num.end()));

    //iterate oveer all candidates , generate permutations for each candidate and check
    for(auto x: candidates) {
        //lambda expression to convert number to digits vector 
        //i.e. 2345 -> {2,3,4,5}
        auto digits = [](int x)-> std::vector<int>{
            std::vector<int> t(6);
            for(int j=0, num=x; j<6; j++) {
                t[5-j] = num %10;
                num /= 10;
            }
            return t;
        };

        //convert number to vector of digits
        std::vector<int> xEements = digits(x);
        //generate all permutations of x and check
        do {
            //convert vector to number
            int currentNum = std::accumulate(xEements.begin(), xEements.end(), 0, [&](int x, int y){return 10*x+y;});
            
            //speed up:
            //skip this permutation if MSB is not 1
            if(currentNum > 199999)
                continue;

            //check all multiples of currentNum till 6X
            bool found = true;
            for(int i=1; i<=6; i++) {
                if(signature(currentNum) != signature(i* currentNum)) {
                    //condition fails, break from loop
                    found = false;
                    break;
                }
            }
            //found one, print and bail out!
            if(found) {
                std::cout << currentNum  << std::endl;
                return 0;
            }
        } while(std::next_permutation(xEements.begin(), xEements.end()));
    }

    return 0;
}

