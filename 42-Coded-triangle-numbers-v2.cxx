#include <iostream>
#include <vector> 
#include <set>
#include <cmath>

//Coded triangle numbers
//Problem 42
//
//The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1); so the first ten triangle numbers are:
//
//1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
//
//By converting each letter in a word to a number corresponding to its alphabetical position and adding these values we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word value is a triangle number then we shall call the word a triangle word.
//
//Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common English words, how many are triangle words?
//
//core idea:
//0. precalculate all triangle nums till t30
//1. read all words and convert to its sum of all alphabetic values
//2. check if a word is triangle
//
// Triangle nums: AP Series
// precalculate triangle numbers till 30 = 30*31/2 =465
// big words are : ENVIRONMENTAL, UNFORTUNATELY -> 13 letters 
// max possible with all Z's = 13 * 26 = 338 (max triangle value) convered by t30;
//
// I/O:
// (base) topo@topobox:~/myRev/cpp/euler$ time cat 42input.txt |./a.out
//162
//
//real	0m0.011s
//user	0m0.011s
//sys	0m0.000s
//(base) topo@topobox:~/myRev/cpp/euler$

std::string readOneWord() {
    std::string word;
    while(true) {
        char c= std::cin.get();
        // no more input
        if(!std::cin)
            break;

        if(c=='"')
            continue;
        if(c==',')
            break;

        word += c;
    }
    //    std::cout << word << std::endl;
    return word;
}

bool isTriagonal(unsigned long x) {
     // Tn = n(n+1)/2
     // Solve the quadratic equation for n
     // n = (-1+sqrt(1+8*x))/2;
     unsigned long n = (-1+sqrt(1+8*x))/2;
     //for this n get Tn
     unsigned long Tn = n*(n+1)/2;

     return Tn==x;
 }


int main() {
    int tri =0;
    while(true) {
        std::string current = readOneWord();
        if(current.empty())
            break;
        int val=0;
        for(auto a: current) {
            //val = delta to A + 1
            val += a - 'A' +1;
        }
        if(isTriagonal(val)) {
            tri++;
            //std::cout << current << " is triangle :" << val << std::endl;
        }
    }

    std::cout << tri << std::endl;
    return 0;
}

