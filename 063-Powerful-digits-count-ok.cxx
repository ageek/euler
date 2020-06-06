#include <iostream>
#include <vector> 


//Powerful digit counts
//Problem 63
//
//The 5-digit number, 16807=7^5, is also a fifth power. Similarly, the 9-digit number, 134217728=8^9, is a ninth power.
//
//How many n-digit positive integers exist which are also an nth power?
//
//Note: - With multiple trials it can be seen that the condition fails when exp>21. so checking till exp 21 is good enough(with base < exp)
//      - This is generic implementation and can handle arbitrary base and exp values, though not needed here
//I/O:
//(base) topo@topobox:~/myRev/cpp/euler$ gpp -O3 063-Powerful-digits-count.cxx
//(base) topo@topobox:~/myRev/cpp/euler$ time ./a.out
//49
//
//real	0m0.090s
//user	0m0.058s
//sys	0m0.000s
//(base) topo@topobox:~/myRev/cpp/euler$

// vec x Int -> vec
std::vector<int> vecxint(std::vector<int>num, int x) {
    std::vector<int> result;
    int carry = 0;
    for(auto a: num) {
        int current = carry + a*x;
        carry = current / 10;
        result.push_back(current % 10);
    }
    while(carry>0) {
        result.push_back(carry %10);
        carry /= 10;
    }
    return result;
}

//int^int -> vec result
std::vector<int> pow(int a, int b) {
    std::vector<int> v; 
    int t=a;
    // 234 -> {4,3,2}
    while(t>0) {
        v.push_back(t%10);
        t /= 10;
    }
    t=b-1;
    while(t>0) {
        v = vecxint(v, a);
        t--;
    }
    return v;
}


int main() {
    //max 21 is enough
    int max=50;

    //Naive, loop and check how many digits are in pow(x,n)
    int count=0;
    for(int a=1; a<max; a++) {
        for(int b=1; b<max; b++) {
            std::vector<int> result = pow(a,b);
            if(result.size() == b) {
                //std::cout << a << "^" << b << ":" << result.size() << std::endl;
                count++;
            }
        }
    }

    std::cout << count << std::endl;
    return 0;
}

