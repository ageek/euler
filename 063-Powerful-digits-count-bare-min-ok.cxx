#include <iostream>
#include <vector> 
#include <cmath>

//Powerful digit counts
//Problem 63
//
//The 5-digit number, 16807=75, is also a fifth power. Similarly, the 9-digit number, 134217728=89, is a ninth power.
//
//How many n-digit positive integers exist which are also an nth power?
//
//core algo:
//calculate all powers of 1-9 ^x 
//and check if the result lies between min and max of x digits
//min of x digits = 10^(x-1) 
//max of x digits = 10^x -1
//e.g. x=3 , min=10^(3-1)=10^2=100
//           max=10^3-1 = 1000-1=999
//
//I/O:
//(base) topo@topobox:~/myRev/cpp/euler$ gpp -O3 063-Powerful-digits-count-bare-min.cxx
//(base) topo@topobox:~/myRev/cpp/euler$ time ./a.out 
//49
//
//real	0m0.004s
//user	0m0.000s
//sys	0m0.002s
//(base) topo@topobox:~/myRev/cpp/euler$


//calculate all powers of 1-9 ^x 
//and check if the result lies between min and max of x digits
//min of x digits = 10^(x-1) 
//max of x digits = 10^x -1
//e.g. x=3 , min=10^(3-1)=10^2=100
//           max=10^3-1 = 1000-1=999
unsigned int check(unsigned int x) {
    unsigned int c=0;
    //range of numbers
    double from = pow(10, x-1);
    double to = pow(10,x) -1; 
    //std::cout << x << ":" << from << "<->" << to << std::endl;
    for(unsigned base=1; base<=9; base++) {
        //calculate base^x
        //compute''1^x'' to ''9^x'', check if they are between ''from'' and ''to''
        double result = 1;
        for(unsigned i=1; i<=x ; i++) {
            //std::cout << base << "^" << i << "=" << result << std::endl;
            result *= base;
        }
        if(result >=from && result<=to) {
            c++;
        }
    }
    return c;
}

int main() {
    unsigned int max=21;
    unsigned int count=0;
    for(int i=1; i<=max; i++) {
        count += check(i);
    }

    std::cout << count << std::endl;
    return 0;
}

