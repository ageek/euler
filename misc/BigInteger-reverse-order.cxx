#include <iostream>
#include <vector> 
#include <cmath>

//-This class 'LargeNumber' is for dealing with very big numbers > MAX supported by C++
//-This class represents numbers in vector format and does all operations in vector format
//
struct LargeNumber: public std::vector<unsigned int> {
    unsigned int maxBase = 10;
    //construct vec from x in reverse format
    //2345 - > {5,4,3,2}
    LargeNumber(unsigned int t) {
        while(t>0) {
            this->push_back(t%10);
            t /= 10;
        }
    }

    // Multiply vector with integer
    // i.e vector x int
    LargeNumber operator *(unsigned int x) const {
        //std::cout << "multiplying " << this->toString() << "*" << x << std::endl;
        if(x==0)
            return 0;
        if(x==1)
            return *this;

        auto result = *this;
        int carry = 0;
        //we'll do inplace replacement of result back to r, so use ref for r
        for(auto& r: result){
            carry +=  x*r;
            r = carry % 10;
            carry /= 10;
        }
        // still have carry? push maxBase wise back to vector
        while(carry>0) {
            result.push_back(carry %10);
            carry /= 10;
        }
        return result;
    }  

    // String representation for *this vector
    // {4,3,2,1} -> 1234
    std::string toString() const {
        std::string res="";
        for(int i=0; i<(*this).size(); i++){
            res = std::to_string((*this)[i])+ res;
        }
        return res;
    }

    // add two numbers represented in vector
    // result = result(left) + right
    LargeNumber operator+(const LargeNumber& right) const {
        //std::cout << "adding:"<< this->toString() << " + " << right.toString() <<  std::endl;
        auto result = *this;
        //make sure both vectors are of same length with 0-padding
        // 234   -> {4,3,2,0,0}
        // 15467 -> {7,6,4,5,1}
        // result-> {1,0,7,5,1} //its in reverse order, print/use it as :15701
        if(result.size() < right.size())
            result.resize(right.size(), 0);

        int carry=0;
        //do in-place replacement of result
        //max i = result.size() and not right.size()
        for(int i=0; i < result.size(); i++) {
            carry += result[i] ;
            if(i < right.size())
                carry += right[i];
            result[i]= carry %10;
            carry /= 10;
        }
        //we are through the loop and still have carry, push it
        if(carry>0) {
            result.push_back(carry);
        }
        return result;
    }

    // Multiply two LargeNumbers
    LargeNumber operator*(const LargeNumber& multiplier) const {
        //std::cout << "Multiplying LargeNumbers:" << this->toString() << "*" << num.toString() << std::endl;
        LargeNumber result = 0;
        for(int i=multiplier.size()-1; i>=0; i--) {
            //use overloaded vec * int
            result = result * 10 + (*this * multiplier[i]);
        }
        return result;
    }


    //compare two LargeNumbers
    bool operator<(const LargeNumber& num) const{
        //if vec.size() are different, its easy
        if(this->size() < num.size())
            return true;
        if(this->size() > num.size())
            return false;
        //else , we need to check element wise, vec with first smaller element is smaller
        for(int i=this->size()-1; i>=0; i--) {
            if(operator[](i) < num[i])
                return true;
            if(operator[](i) > num[i])
                return false;
        }
        return false;
    }
};  //end of class LargeNumber



LargeNumber pow(int a, int b) {
    LargeNumber v(a);
    std::cout << "calculating -->" << a << "^" << b << std::endl;
    int t=b-1;
    while(t>0) {
        //overloaded vector * int
        v = v * a;
        t--;
    }
    return v;
}
int main() {
    LargeNumber result=0;
    result = LargeNumber(234568787) * 87875;
    for(auto x: result) {
        std::cout << x << ",";
    }
    std::cout << std::endl;

    LargeNumber a = 34568;
    LargeNumber b = 34567;
    LargeNumber c = 1;
    result=a+b;
    result = result + c;
    for(auto x: result) {
        std::cout << x << ",";
    }
    std::cout << std::endl;

    result = pow(1875,29);
    for(auto x: result) {
        std::cout << x << ",";
    }
    std::cout << std::endl;

    if (a < b)
        std::cout << a.toString() << "<" << b.toString() << std::endl;
    else 
        std::cout << a.toString() << "> or="  << b.toString() << std::endl;


    result = a*b;
    for(auto x: result) {
        std::cout << x << ",";
    }
    std::cout << std::endl;

    return 0;

}

