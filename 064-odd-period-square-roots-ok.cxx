#include <iostream>
#include <cmath>
//Odd period square roots
//Problem 64
//
//All square roots are periodic when written as continued fractions and can be written in the form:
//N−−√=a0+1a1+1a2+1a3+…
//
//For example, let us consider 23−−√:
//
//23−−√=4+23−−√−4=4+1123√−4=4+11+23√−37
//
//If we continue we would get the following expansion:
//23−−√=4+11+13+11+18+…
//
//The process can be summarised as follows:
//
//a0=4,123√−4=23√+47=1+23√−37
//
//a1=1,723√−3=7(23√+3)14=3+23√−32
//a2=3,223√−3=2(23√+3)14=1+23√−47
//a3=1,723√−4=7(23√+4)7=8+23−−√−4
//a4=8,123√−4=23√+47=1+23√−37
//a5=1,723√−3=7(23√+3)14=3+23√−32
//a6=3,223√−3=2(23√+3)14=1+23√−47
//a7=1,723√−4=7(23√+4)7=8+23−−√−4
//
//
//It can be seen that the sequence is repeating. For conciseness, we use the notation 23−−√=[4;(1,3,1,8)]
//
//, to indicate that the block (1,3,1,8) repeats indefinitely.
//
//The first ten continued fraction representations of (irrational) square roots are:
//
//2–√=[1;(2)]
//, period=1
//3–√=[1;(1,2)], period=2
//5–√=[2;(4)], period=1
//6–√=[2;(2,4)], period=2
//7–√=[2;(1,1,1,4)], period=4
//8–√=[2;(1,4)], period=2
//10−−√=[3;(6)], period=1
//11−−√=[3;(3,6)], period=2
//12−−√=[3;(2,6)], period=2
//13−−√=[3;(1,1,1,1,6)], period=5
//
//Exactly four continued fractions, for N≤13
//
//, have an odd period.
//
//How many continued fractions for N≤10000
//have an odd period?
//
//core idea: 
//  - core idea is based on wiki article here: 
//  - ->Refer wikipedia article for details on period length and how to obtain the same: https://en.wikipedia.org/wiki/Periodic_continued_fraction
//  - -> FOr detailed explanation refer the excellent article on CF etc: http://www.maths.surrey.ac.uk/hosted-sites/R.Knott/Fibonacci/cfINTRO.html
//I/O:
//(base) topo@topobox:~/myRev/cpp/euler$ gpp -O3 064-odd-period-square-roots-ok.cxx 
//(base) topo@topobox:~/myRev/cpp/euler$ time ./a.out 
//1322
//
//real	0m0.024s
//user	0m0.009s
//sys	0m0.004s
//(base) topo@topobox:~/myRev/cpp/euler$ 
//

int main() {
    unsigned int result=0; 
    unsigned int max=10000;

    for(unsigned int n=2; n<=max; n++) {
        //base case
        unsigned int m = 0; 
        unsigned int d = 1;
        unsigned int root = sqrt(n);
        unsigned int a = root;
        unsigned int period = 0;

        //skip sqr numbers
        if( root * root == n )
            continue;

        //refer wiki article for the core idea: 
        //The algorithm terminates when this triplet is the same as one encountered before. 
        //The algorithm can also terminate on ai when ai = 2 a0,[7] which is easier to implement.
        while(a != 2*root ){
            m = d*a -  m;
            d = (n-m*m)/d;
            a = (root+m)/d;

            //track period length
            period++;
        }

        //std::cout << n << "'s period lenght='" << period << std::endl;
        //we are looking for odd period lenghts ONLY
        if(period%2==1)
            result++;
    }
    std::cout << result << std::endl;
    return 0;
}
