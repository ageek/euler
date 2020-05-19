#include<iostream>
#include<vector>

//Power digit sum
//Problem 16
//
//2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
//
//What is the sum of the digits of the number 2^1000?
//
//I/O
// echo "2 1000"|./a.out

int main() {
    int verbose = false;

    int base;
    std::cin >> base;

    int exponent;
    std::cin >> exponent;

    // a vector to store the digits for every multiplication by 2
    std::vector<int> digits;

    // to start with
    digits.push_back(2);

    // when base =2, exp=10, digits = {1, 0, 2, 4}

    int digSum=0;
    while(--exponent > 0) {
        //iterate over all the elements of vector and double each number
        //maintaining a carry to MSB as needed
        //
        int carry =0;
        for(int x=digits.size()-1; x>=0; x--) {
            int lastx2 = carry+2*digits[x];
            //clear carry
            carry = 0;
            int lastDoubleDigit =  lastx2 % 10;
            if(lastx2 >=10) {
                carry =1;
            }
            if(verbose)
                std::cout << "digitx[x]=" << digits[x] << " 2*digits[x]= " << lastx2 << std::endl;

            digits[x] = lastDoubleDigit;

            //if 2*MSB >= 10, and x=0, we are done with loop, but still have carry, so we must insert() carry at the beginning
            if(carry>0 && x==0) {
                digits.insert(digits.begin(), carry);
            }
        }

    }
    std::cout << std::endl;
    for(auto a:digits) {
        digSum +=a;
    }
    std::cout << digSum << std::endl;

    return 0;
}
