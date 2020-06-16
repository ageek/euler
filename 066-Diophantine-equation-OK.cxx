#include <iostream>
#include <vector> 
#include <cmath>
//Diophantine equation
//Problem 66
//
//Consider quadratic Diophantine equations of the form:
//
//x^2 – Dy^2 = 1
//
//For example, when D=13, the minimal solution in x is 649^2 – 13×180^2 = 1.
//
//It can be assumed that there are no solutions in positive integers when D is square.
//
//By finding minimal solutions in x for D = {2, 3, 5, 6, 7}, we obtain the following:
//
//3^2 – 2×2^2 = 1
//2^2 – 3×1^2 = 1
//9^2 – 5×4^2 = 1
//5^2 – 6×2^2 = 1
//8^2 – 7×3^2 = 1
//
//Hence, by considering minimal solutions in x for D ≤ 7, the largest x is obtained when D=5.
//
//Find the value of D ≤ 1000 in minimal solutions of x for which the largest value of x is obtained.
//
//Core algo: 
//1. we have to deal with big numbers (> max supported by C++)so lets use the vectorized LargeNumber technique
//2. Diophantine equation: sqrt(D) is a continous fraction represented by x/y (approximated): https://brilliant.org/wiki/quadratic-diophantine-equations-pells-equation/
//3. https://en.wikipedia.org/wiki/Pell%27s_equation
//Ref stbrumme's solution 
//I/O: 
//(base) topo@topobox:~/myRev/cpp/euler$ gpp -O3 066-Diophantine-equation.cxx
//(base) topo@topobox:~/myRev/cpp/euler$ time echo 1000|./a.out
//661
//
//real	0m0.124s
//user	0m0.110s
//sys	0m0.004s
//(base) topo@topobox:~/myRev/cpp/euler$ 


//1+ D x y^2  =x^2
unsigned int max;

//-This class 'LargeNumber' is for dealing with very big numbers > MAX supported by C++
//-This class represents numbers in vector format and does all operations in vector format
//Note: representing Numbers in reverse vector format eases * + etc operation
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


int main() {
    //default is 1000 for this Qs
    std::cin >> max;
    unsigned long long bestD = 2; 
    LargeNumber bestX = 3;

    //check for all values of D
    for(int d=3; d<=max; d++) {
        unsigned int root = sqrt(d);
        if(root*root ==d)
            continue;
        unsigned int a           = root;
        unsigned int numerator   = 0;
        unsigned int denominator = 1;

        // keep only the most recent 3 numerators and denominators while diverging
        // Numerators
        LargeNumber x0=0, x1=1, x2=root;
        // Denominators
        LargeNumber y0=0, y1=0, y2=1;    // denominators

        // find better approximations until the exact solution is found
        while (true)
        {
            numerator   = denominator * a - numerator;
            denominator = (d - numerator * numerator) / denominator;
            a = (root + numerator) / denominator;

            //as numbers are Large, std::move speeds up overall process
            x0 = std::move(x1);
            x1 = std::move(x2); 
            x2 = x1*a + x0;

            y0 = std::move(y1); 
            y1 = std::move(y2); 
            y2 = y1 * a+ y0;

            // avoid subtraction (to keep LargeNumber's code short)
            // x*x         = 1 + d*y*y
            if (x2*x2 == (y2*y2*d + 1))
                break;
        }
        // biggest x so far ?
        if (bestX < x2)
        {
            bestX = x2;
            bestD = d;
        }
    }

    std::cout << bestD << std::endl;
    //std::cout << bestD << ":" << bestX.toString() << std::endl;
    return 0;
}

