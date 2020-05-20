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
//core algo:
//1. deal with all numbers in vector
//2. use vector add() to add two numbers
//3. check if sum is Palindrome
//4. if not check sum+flippedSum is Palindrome, 
//5. continue with loop for max 50 flips, keeping a count if Lychrels
//
//I/O:
//(base) topo@topobox:~/myRev/cpp/euler$ gpp -O3 Lychrel-numbers.cxx
//(base) topo@topobox:~/myRev/cpp/euler$ time ./a.out
//249
//
//real	0m0.100s
//user	0m0.069s
//sys	0m0.000s
//(base) topo@topobox:~/myRev/cpp/euler$ time ./a.out


// add two numbers represented in vector
// left + right = result
std::vector<int> add( std::vector<int> left, std::vector<int> right)  {
    std::vector<int> sum;
    // run a loop for max(left.size(), right.size())
    int carry=0;
    for(int i=1; i <= std::max(left.size(), right.size()); i++) {
        int t = 0;
        t += carry ;
        //reset carry to 0
        carry = 0;
        int l=left.size() - i;
        int r=right.size() - i;
        if(l >= 0)
            t += left[left.size()-i] ;
        if(r >= 0)
            t += right[right.size()-i];

        sum.insert(sum.begin(), t % 10);
        //std::cout << t%10 << ", ";
        if(t/10 > 0) {
            carry = t/10;
        }
    }
    //we are through the loop and still have carry, push it
    if(carry>0)
        sum.insert(sum.begin(), carry);

    return sum;
}


int main() {

    //default to 10000 as per Prob stmt.
    int maxNum = 10000;
    int maxFlips = 50;

    //number to vector representation
    // 2345 -> {2,3,4,5}
    auto num2vec = [](int num) ->std::vector<int> {
        std::vector<int> result;

        while(num>0) {
            result.insert(result.begin(), num%10);
            num /= 10;
        }
        return result;
    };

    //Lychrel counts
    int count = 0;
    for(int i=11; i<=maxNum; i++) {
        maxFlips = 50;
        std::vector<int> current = num2vec(i);
        //even after 50 flips, sum is not a Palindrome -> Lychrel
        while(maxFlips > 0) {
            //flip the number
            std::vector<int> flipped=current;
            std::reverse(flipped.begin(), flipped.end());

            //sum current + flipped and check if its a palindrome
            auto sum = add(current, flipped);

            std::vector<int> flippedSum = sum;
            std::reverse(flippedSum.begin(), flippedSum.end());

           // // check some of the Lychrel number's behavior till 50 flips
           // if(i==196 || i==295 || i==394 || i==494) {
           //     std::cout << maxFlips;
           //     std::cout<< ":current=" ;
           //     for(auto x:current)
           //         std::cout << x << ",";

           //     std::cout<< ",flipped=" ;
           //     for(auto x:flipped)
           //         std::cout << x << ",";

           //     std::cout<< ", sum="; 
           //     for(auto x:sum)
           //         std::cout << x << ",";
           //     std::cout << ", flipSum=" ;
           //     for(auto x:flippedSum)
           //         std::cout << x << ",";
           //     std::cout << std::endl;
           // }
            if(sum == flippedSum) {
                // not a Lychrel, check next number
                break;
            }
            //else 
            //efficient copy using std::move
            current = std::move(sum);
            maxFlips--;
        }
        //flipped 50 times but no Palindromic sum found
        if(maxFlips == 0) {
            //std::cout << i << std::endl;
            count ++;
        }
    }

    std::cout << count << std::endl;
    return 0;
}

