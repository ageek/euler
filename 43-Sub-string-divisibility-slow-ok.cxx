#include <iostream>
#include <vector> 
#include <set>
#include <algorithm>

//Sub-string divisibility
//Problem 43
//
//The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order, but it also has a rather interesting sub-string divisibility property.
//
//Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:
//
//    d2d3d4=406 is divisible by 2
//    d3d4d5=063 is divisible by 3
//    d4d5d6=635 is divisible by 5
//    d5d6d7=357 is divisible by 7
//    d6d7d8=572 is divisible by 11
//    d7d8d9=728 is divisible by 13
//    d8d9d10=289 is divisible by 17
//
//Find the sum of all 0 to 9 pandigital numbers with this property.
//
bool isPanDivisible(std::string x) {
    std::vector<int> divs={2,3,5,7,11,13,17};
    int span=3;
    int pos =1;
    while(pos < 8 ) {
        //std::cout << pos << ":" << x.substr(pos, span) << std::endl;
        long num = std::stol(x.substr(pos, span));
        //std::cout << num << std::endl;
        //if one fails divisibility check, bail out
        if(num % divs[pos-1] !=0 )
            return false;
        pos++;
    }
//    std::cout << x << " is pan divisible" << std::endl;
    return true;
}

int main() {
    //isPanDivisible("1406357289");
    long sum = 0;
    std::string str = "0123456789";
    std::set<std::string> pandigitals;
    do {
        //std::cout << "checking " << str << std::endl;
        if(isPanDivisible(str)){
            sum += std::stol(str);
            pandigitals.insert(str);
        }

    }while(std::next_permutation(str.begin(), str.end()));
    std::cout << sum << std::endl;

    return 0;
}

