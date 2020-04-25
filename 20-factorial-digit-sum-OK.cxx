#include <iostream>
#include <vector> 

//Factorial digit sum
//Problem 20
//
//n! means n × (n − 1) × ... × 3 × 2 × 1
//
//For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
//and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
//
//Find the sum of the digits in the number 100!
//
//I/O:
//echo "1000"|./a.out
//(base) topo@topobox:~/myRev/cpp/euler$ echo "1000" |./a.out
//10539
//(base) topo@topobox:~/myRev/cpp/euler$


int main() {
    int num;
    std::cin >> num;

    std::vector<int> facResult;
    //start with 1
    facResult.push_back(1);


    for(int i=2; i<= num; i++) {
        int carry =0;
        for(int x=facResult.size()-1; x>=0; x--) {
            // last digit multiplied by i
            int lx = carry + facResult[x] * i;

            //clear carry
            carry =0;

            int l = lx % 10;
            //overwrite digit at x
            facResult[x] = l;

            if(lx>=10) {
                //we have carry
                carry = (lx/10);
            }
//            std::cout << "lx=" << lx << ", l=" << l << ", carry=" << carry << ", facResult=" ;
        }
        //loop over, still have carry? insert
        //insert one digit at a time, till we exchause all digits in carry
        while(carry>0){
            facResult.insert(facResult.begin(), carry%10);
            carry /= 10;
        }
//        for(auto a: facResult)
//            std::cout << a << ",";
//        std::cout << std::endl;
    }


    unsigned long digitSum=0;
    for(auto a: facResult) {
        digitSum += a;
        //std::cout << a ;
    }
    std::cout << digitSum << std::endl;

    return 0;
}

