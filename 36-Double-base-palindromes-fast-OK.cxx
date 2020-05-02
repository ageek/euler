#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

//Double-base palindromes
//Problem 36
//
//The decimal number, 585 = 1001001001 (binary), is palindromic in both bases.
//
//Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
//
//(Please note that the palindromic number, in either base, may not include leading zeros.)
//
//I/O:
//(base) topo@topobox:~/euler$ time echo 1000000|./a.out 
//872187
//
//real	0m0.111s
//user	0m0.043s
//sys	0m0.001s
//(base) topo@topobox:~/euler$

bool isPalindrome(int num) {
    int t = num;
    int rev = 0;
    int p =0;
    // 197  
    while(t>0) {
        rev = (t % 10) + rev * 10;
        t /= 10;
    }
    if(num == rev) {
        //std::cout << num << " is palindrome " << std::endl;
        return true;
    }

    return false;
}

//binary can be huge, (out of range) so lets represent binary of decimal in std::string
//convert from decimal to binary string
std::string boolean(int num) {
    std::string res="";

    while(num >0) {
        if(num %2 == 0)
            res += "0";
        else 
            res += "1";

        num /=2;
    }
    //std::cout << res << std::endl;
    return res;
}

int main() {
    // max number limit, here it is 10^6
    int limit;
    std::cin >> limit;

    int sum = 0;
    for(int i=1; i< limit; i++) {
        //first check if decimal number i is Palindrome
        if(isPalindrome(i)) {
            //if yes, get boolean and check if boolean is also Palindrome
            std::string t = boolean(i);
            //reverse t
            // 
            // int n= t.length();
            // std::string l=t;
            // for(int i=0; i< n/2; i++) {
            //     std::swap(t[i], t[n-i-1]);
            // }
            // OR
            std::string l=t;
            std::reverse(l.begin(), l.end());
            //if boolean is also palindrome, sum it up
            if ((t == l)) {
                sum += i;
                //    std::cout << i << ", " << t << std::endl;
            }
        }
    }
    std::cout << sum << std::endl;
    return 0;
}

