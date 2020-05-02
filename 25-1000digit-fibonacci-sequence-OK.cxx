#include <iostream>
#include <vector> 

//1000-digit Fibonacci number
//Problem 25
//
//The Fibonacci sequence is defined by the recurrence relation:
//
//    Fz = Fz−1 + Fz−2, where F1 = 1 and F2 = 1.
//
//Hence the first 12 terms will be:
//
//    F1 = 1
//    F2 = 1
//    F3 = 2
//    F4 = 3
//    F5 = 5
//    F6 = 8
//    F7 = 13
//    F8 = 21
//    F9 = 34
//    F10 = 55
//    F11 = 89
//    F12 = 144
//
//The 12th term, F12, is the first term to contain three digits.
//
//What is the index of the first term in the Fibonacci sequence to contain 1000 digits?
//(base) topo@topobox:~/myRev/cpp/euler$ time echo 1000 |./a.out 
//4782
//
//real	0m1.064s
//user	0m1.013s
//sys	0m0.004s
//(base) topo@topobox:~/myRev/cpp/euler$

std::vector<int> add( std::vector<int>, std::vector<int>) ;


// left + right = result
std::vector<int> add( std::vector<int> left, std::vector<int> right)  {
    std::vector<int> sum;

    // run a loop for max(left.size(), right.size())
    //
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

    // digitcount
    int digCount;
    std::cin >> digCount; 

    std::vector<int> Fy, Fx, Fz;

    //starting point
    Fy.push_back(2);
    Fx.push_back(1);
    // F1 = 1
    // F2 = 2
    // Seq: Fx, Fy, Fz
    // Fz = Fy + Fx ;
    // i.e. F3 = F2 + F1


    int index=3;
    int size =1;
    while(size < digCount && index++){
        //calculate Fz
        Fz = add(Fy , Fx);
//        for(auto a: Fz)
//            std::cout << a ; 
//        std::cout << "=";
//        for(auto a: Fy)
//            std::cout << a ; 
//        std::cout << "+";
//        for(auto a: Fx)
//            std::cout << a ; 
//
//        std::cout <<", Index="<< index << ", digitCount=" << Fz.size() << std::endl;

        // move up 1  step 
        Fx = Fy;
        Fy = Fz;

        // check no of digits in Fz
        size = Fz.size();

    }
//    for(auto a: Fz)
//        std::cout << a;

//    std::cout << std::endl;
    std::cout << index <<  std::endl;


    return 0;
}

