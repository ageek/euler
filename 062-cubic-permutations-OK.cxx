#include <iostream>
#include <vector> 
#include <algorithm>
#include <map>

//Cubic permutations
//Problem 62
//
//The cube, 41063625 (345^3), can be permuted to produce two other cubes: 56623104 (384^3) and 66430125 (405^3). In fact, 41063625 is the smallest cube which has exactly three permutations of its digits which are also cube.
//
//Find the smallest cube for which exactly five permutations of its digits are cube.
//
//core algo: 
//1. create a map std::string > std::vector<unsigned int> 
//2.    signature -> {i^3, j^3, ...}
//3. find an entry in the map where size of vec =maxPermutes
//I/O:
//(base) topo@topobox:~/euler$ time echo 5|./a.out
//127035954683
//
//real	0m0.035s
//user	0m0.015s
//sys	0m0.004s
//(base) topo@topobox:~/euler$

//number -> signature
//each number gets a signature where position value of index i indicates occurence count of that index
// 11234 -> 0211100000 [0- none, 1- 2 times, 2-once, 3-once, 4-once, rest all 0 ]
std::string signature(unsigned long long x) {
    //    unsigned long long num = x;
    std::string fp("0000000000");
    while(x > 0) {
        int t = x%10;
        x /= 10;
        fp[t] += 1;
    }
    //    std::cout << num << ":" << fp << std::endl;
    return fp;
}

int main() {
    //create list of cubes upto large num
    //Note: we'll bail out much earlier, the moment we find maxPermute condition satisfies
    unsigned long BIGNUM = 99999;
    std::map<std::string, std::vector<unsigned long long>> cache;
    //default is 5
    int maxPermutes ;
    std::cin >>  maxPermutes; 

    //keep a track of which signature?
    std::string keep ="";
    //Note: i must be ULL else i*i*i will throw integer overlow warning and lead to incorrect signature 
    //    (base) topo@topobox:~/euler$ gpp -O3 062-cubic-permutations.cxx 
    //062-cubic-permutations.cxx: In function ‘int main()’:
    //062-cubic-permutations.cxx:36:35: warning: integer overflow in expression [-Woverflow]
    //     unsigned long long t=4821*4821*4821;
    //                          ~~~~~~~~~^~~~~
    //062-cubic-permutations.cxx:38:16: warning: integer overflow in expression [-Woverflow]
    //     t=5748*5748*5748;
    //       ~~~~~~~~~^~~~~
    //(base) topo@topobox:~/euler$
    for(unsigned long long  i=111; i<=BIGNUM; i++) {
        unsigned long long x = i*i*i;
        std::string s = signature(x);
        cache[s].push_back(i);
        if(cache[s].size()==maxPermutes) {
            //found one, bail out !
            keep=s;
            break;
        }
    }
    //std::cout << keep << ":";
    //print all maxPermutes no whose cubes are permutations of each other
    //for(auto x: cache[keep])
    //    std::cout << x << ",";

    //print the cube of smallest 
    unsigned long long smallest = *std::min_element(cache[keep].begin(), cache[keep].end());
    std::cout << (smallest*smallest*smallest) << std::endl;
    return 0;
}

