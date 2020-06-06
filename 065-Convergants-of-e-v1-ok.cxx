#include <iostream>
#include <vector> 
//Convergents of e
//Problem 65
//
//The square root of 2 can be written as an infinite continued fraction //2–√=1+12+12+12+12+...
//The infinite continued fraction can be written, 2–√=[1;(2)]
//, (2) indicates that 2 repeats ad infinitum. In a similar way, 23−−√=[4;(1,3,1,8)]
//It turns out that the sequence of partial values of continued fractions for square roots provide the best rational approximations. Let us consider the convergents for 2–√
//1+12=321+12+12=751+12+12+12=17121+12+12+12+12=4129
//
//Hence the sequence of the first ten convergents for 2–√
//are:
//1,32,75,1712,4129,9970,239169,577408,1393985,33632378,...
//
//What is most surprising is that the important mathematical constant,
//e=[2;1,2,1,1,4,1,1,6,1,...,1,2k,1,...]
//The first ten terms in the sequence of convergents for e are:
//2,3,83,114,197,8732,10639,19371,1264465,1457536,...
//The sum of digits in the numerator of the 10th convergent is 1+4+5+7=17
//
//Find the sum of digits in the numerator of the 100th convergent of the continued fraction for e
//
//Ref: stephan-brumme.com      
//The continued fraction forms a regular pattern where every third increases by two and the rest are ones
// ||   k   || numerator || continuous fraction ||
// ||   1   ||      2    ||          1          ||
// ||   2   ||      3    ||          2          ||
// ||   3   ||      8    ||          1          ||
// ||   4   ||     11    ||          1          ||
// ||   5   ||     19    ||          4          ||
// ||   6   ||     87    ||          1          ||
// ||   7   ||    106    ||          1          ||
// ||   8   ||    193    ||          6          ||
// ||   9   ||   1264    ||          1          ||
// ||  10   ||   1457    ||          1          ||
//
//Note: Numerator follows the pattern: 
//      n[k] = (a[k] * n[k-1] )+ n[k-2] 
//
// All we have to do is writing a simple ''for''-loop that keeps tracks of the two most recent numerators.
// The continuous fraction is `1` if `index mod 3 != 2` and `2k` if `index mod 3 == 2`.
//I/O:
//base) topo@topobox:~/myRev/cpp/euler$ gpp -O3 065-Convergants-of-e.cxx 
//(base) topo@topobox:~/myRev/cpp/euler$ time ./a.out 
//272
//
//real	0m0.004s
//user	0m0.003s
//sys	0m0.000s
//(base) topo@topobox:~/myRev/cpp/euler$ 
//


// add two numbers represented in vector
// left + right = result
// vector ordering: same as num representation
// 2345 -> {2,3,4,5}
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

// 1234 -> {1,2,3,4}
// vec x Int -> vec
std::vector<int> vecxint(std::vector<int>num, int x) {
    std::vector<int> result;
    int carry = 0;
    for(int i=num.size()-1; i>=0; i--) {
        int current = carry + x*num[i];
        carry = current / 10;
        result.insert(result.begin(), current % 10);
    }
    while(carry>0) {
        result.insert(result.begin(), carry %10);
        carry /= 10;
    }
    return result;
}

int main() {
    //calculate the numerator pattern and keep track of result for 100th numerator
    //
    //234 -> {2,3,4}
    auto vec2int = [](int num)->std::vector<int>{ 
        std::vector<int> res;
        while(num>0) {
            res.insert(res.begin(), num%10);
            num /= 10;
        }
        return res;
    }; 
    
//The continued fraction forms a regular pattern where every third increases by two and the rest are ones
// ||   k   || numerator || continuous fraction ||
// ||   1   ||      2    ||          1          ||
// ||   2   ||      3    ||          2          ||
// ||   3   ||      8    ||          1          ||
// ||   4   ||     11    ||          1          ||
// ||   5   ||     19    ||          4          ||
// ||   6   ||     87    ||          1          ||
// ||   7   ||    106    ||          1          ||
// ||   8   ||    193    ||          6          ||
// ||   9   ||   1264    ||          1          ||
    //base
    std::vector<int> d = vec2int(1);
    //first element
    //nk = ak * nk_1 + nk_2
    std::vector<int> current = vec2int(2);
    for(int i=2; i<=100; i++) {
        std::vector<int> temp = d;
        int ak = (i % 3 == 0) ? 2 * (i / 3) : 1;
        d = current; 
        //second element 
        current  = add(vecxint(d , ak) , temp);
    }

    //for 100th , get the sum of digits
    unsigned int sum=0;
    for(auto x: current) {
        while(x>0) {
            sum += x%10;
            x /= 10;
        }
    }

    std::cout << sum << std::endl;
    return 0;
}

