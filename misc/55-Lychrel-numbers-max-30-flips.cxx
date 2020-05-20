#include <iostream>
#include <vector> 
#include <set>
#include <algorithm>
#include <string>

//Lychrel numbers
//Problem 55
//
//If we take 47, reverse and add, 47 + 74 = 121, which is palindromic.
//
//Not all numbers produce palindromes so quickly. For example,
//
//349 + 943 = 1292,
//1292 + 2921 = 4213
//4213 + 3124 = 7337
//
//That is, 349 took three iterations to arrive at a palindrome.
//
//Although no one has proved it yet, it is thought that some numbers, like 196, never produce a palindrome. A number that never forms a palindrome through the reverse and add process is called a Lychrel number. Due to the theoretical nature of these numbers, and for the purpose of this problem, we shall assume that a number is Lychrel until proven otherwise. In addition you are given that for every number below ten-thousand, it will either (i) become a palindrome in less than fifty iterations, or, (ii) no one, with all the computing power that exists, has managed so far to map it to a palindrome. In fact, 10677 is the first number to be shown to require over fifty iterations before producing a palindrome: 4668731596684224866951378664 (53 iterations, 28-digits).
//
//Surprisingly, there are palindromic numbers that are themselves Lychrel numbers; the first example is 4994.
//
//How many Lychrel numbers are there below ten-thousand?
//
//NOTE: Wording was modified slightly on 24 April 2007 to emphasise the theoretical nature of Lychrel numbers.
//


int main() {

    int maxNum = 10000;
    int maxFlips = 50;

    auto flip = [](unsigned long long x)->unsigned long long {
        unsigned long long result = 0;
        while(x >0) {
            result = result * 10 + x%10;
            x /= 10;
        }
        return result;
    };

    int count = 0;
    for(int i=11; i<=maxNum; i++) {
        //after 30 flips, sums > max range of ULL
        maxFlips = 30;
        unsigned long long current = i;
        //even after 50 flips, sum is not a Palindrome -> Lychrel
        while(maxFlips > 0) {
            unsigned long long flipped = flip(current);
            unsigned long long sum = current + flipped;

            //if(i==196 || i==295 || i==394 || i==494)
            //std::cout << maxFlips << ":current=" <<current << ", flipped=" << flipped << ", sum=" << sum << ", flipSum=" << flip(sum) << std::endl;

            if(sum == flip(sum)) {
                break;
            }
            //else 
            current = sum;
            maxFlips --;
        }
        //flipped 50 times but no Palindromic sum found
        if(maxFlips == 0) {
            count ++;
        }
    }
    std::cout << count << std::endl;

    return 0;
}

