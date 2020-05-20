#include <iostream>
#include <vector> 

//Problem 17
//
//If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
//
//If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?
//
//NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. 
//The use of "and" when writing out numbers is in compliance with British usage.
//I/O:
//echo "1000" | ./a.out
//example
//echo "99" | ./a.out

std::string numberLetter(int maxNum);


std::string numberLetter(int maxNum) {
    std::string unit[10] = {"zero", "one", "two","three", "four", "five", "six","seven", "eight", "nine"};
    std::string tens[10] = {"","ten", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    std::string teens[10] = {"","eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eightteen", "nineteen"};

    std::string hundred = "hundred";
    std::string AND = "and";
    std::string space = " ";

    std::string output = "";

    int test = maxNum;
    int t =0;

    if(test == 1000) {
        output += "One thousand";
    } 

    if(test % 100 == 0) {
        t = test/100 ;
        output = output + unit[t] + space + hundred;
    } else if(100 < test  && test < 1000) {
        t = test/100; 
        output += unit[t] + space + hundred + space + AND + space;
        test = test%100;
    }
    //std::cout << output << "--" << std::endl;

    if(test <100) {
        if(10 < test && test < 20) {
            t = test - 10 ;
            output += teens[t];
        } else if(test % 10==0) {
            //multiples of 10
            t = test/10 ;
            output += tens[t];
        } else {
            // <100 & not a multiple of 10
            int ten = test/10 ;
            int zero = test % 10;
            //if number < 10
            if(ten==0) {
                output +=  unit[zero];
            } else {
                output += tens[ten] + space + unit[zero];
            }
        } 
    }

    //std::cout << output << ":" << output.length() << std::endl ;
    return output;
}

int main() {
    int maxNum;
    std::cin >> maxNum ;

    int letterCount = 0;
    std::string alpha="";

    for(int i=1; i<=maxNum; i++ ) {
        alpha = numberLetter(i);
        letterCount +=  alpha.length();
    }

    std::cout << letterCount << std::endl;
}
