#include <iostream>
#include <vector> 
#include <set>

//Pandigital products
//Problem 32
//
//We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.
//
//The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.
//
//Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.
//HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.
//
//

bool isPandigital(int multiplicand, int multiplier) {
    // list of allowed digits
    std::set<int> digs = {1,2,3,4,5,6,7,8,9};
    std::set<int> all = {multiplicand * multiplier, multiplicand,  multiplier};
    bool result = false;

    for(auto a: all) {
        while(a>0) {
            int t = a%10;
            // we dont have 0 in the list of allowed digits
            if(t==0)
                return false;

            //remove one element at a time
            digs.erase(t);
            a /= 10;
        }
    }
    // if digs.size()==0
    if (digs.size()==0)
        return true;

    return result;
}
int main() {

    //    isPandigital(39,186);

    std::set<std::pair<int,int>> panDigits;
    std::set<int> all;

    for(int a=1; a<=1999; a++) {
        for(int b=1999; b>=1; b--) {
            if (a==b)
                continue;

            //check total dig count of a, b, a*b 
            int d=0;
            std::set<int> digs = {a, b, a*b};
            for(auto a: digs) {
                while(a>0) {
                    d +=1;
                    a /=10;
                }
            }

            if(d==9 && isPandigital(a, b) ) {
                //panDigits.insert(std::make_pair(a,b));
//                std::cout << a << "*" << b << "=" << a * b << std::endl;
                all.insert(a*b);
            }

        }
    }
    //    for(auto a: panDigits) {
    //        std::cout << a.first << "*" << a.second << "=" << a.first * a.second << std::endl;
    //    }
    //
    int sum = 0;
    for(auto a: all){
        sum += a;
    }

    std::cout << sum << std::endl;
    return 0;
}

