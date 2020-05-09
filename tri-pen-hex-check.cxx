#include <iostream>
#include <vector> 
#include <cmath>

//print triagonal, pentagonal, hexagonal numbers

bool isTriagonal(unsigned long x) {
    // Tn = n(n+1)/2
    // Solve the quadratic equation for n
    // n = (-1+sqrt(1+8*x))/2;
    unsigned long n = (-1+sqrt(1+8*x))/2;
    //for this n get Tn
    unsigned long Tn = n*(n+1)/2;

    return Tn==x;
}

bool isPentagonal(int x) {
    // Pn = n(3n-1)/2
    unsigned long n = (1+sqrt(1+24*x))/6;
    unsigned long Pn = n*(3*n-1)/2;
    return Pn==x;
}

bool isHexagonal(int x) {
    // Hn = n(2n-1)
    unsigned long n = (1+sqrt(1+8*x))/4;
    unsigned long Hn = n*(2*n-1);
    return Hn==x;
}


int main() {
    int limit=500;
    //print separately
    //
    std::cout << "Triangles:" ;
    for(int i=1; i<=limit; i++) {
        if(isTriagonal(i))
            std::cout << i << ",";
    }
    std::cout << std::endl;
    //print separately
    std::cout << "Pentagonal:" ;
    for(int i=1; i<=limit; i++) {
        if(isPentagonal(i))
            std::cout << i << ",";
    }
    std::cout << std::endl;
    //print separately
    std::cout << "Hexagonal:" ;
    for(int i=1; i<=limit; i++) {
        if(isHexagonal(i))
            std::cout << i << ",";
    }   std::cout << std::endl;
    std::cout << std::endl;
    return 0;
}

