#include <iostream>
#include <string>
#include <vector> 
#include <set>
#include <algorithm>
//Magic 5-gon ring
//Problem 68
//
//Consider the following "magic" 3-gon ring, filled with the numbers 1 to 6, and each line adding to nine.
//
//Working clockwise, and starting from the group of three with the numerically lowest external node (4,3,2 in this example), each solution can be described uniquely. For example, the above solution can be described by the set: 4,3,2; 6,2,1; 5,1,3.
//
//It is possible to complete the ring with four different totals: 9, 10, 11, and 12. There are eight solutions in total.
//Total	Solution Set
//9	4,2,3; 5,3,1; 6,1,2
//9	4,3,2; 6,2,1; 5,1,3
//10	2,3,5; 4,5,1; 6,1,3
//10	2,5,3; 6,3,1; 4,1,5
//11	1,4,6; 3,6,2; 5,2,4
//11	1,6,4; 5,4,2; 3,2,6
//12	1,5,6; 2,6,4; 3,4,5
//12	1,6,5; 3,5,4; 2,4,6
//
//By concatenating each group it is possible to form 9-digit strings; the maximum string for a 3-gon ring is 432621513.
//
//Using the numbers 1 to 10, and depending on arrangements, it is possible to form 16- and 17-digit strings. What is the maximum 16-digit string for a "magic" 5-gon ring?
//ref: stbrummes
//I/O:
//(base) topo@topobox:~/myRev/cpp/euler$ gpp -O3 068-Magic-5-gon.cxx
//(base) topo@topobox:~/myRev/cpp/euler$ echo "14 5"|./a.out
//6531031914842725
//(base) topo@topobox:~/myRev/cpp/euler$
//


int ringSize;
int tripletSum;
//valid ring strings 
std::set<std::string> elements;

void checkTriplet(std::vector<int> inner, std::vector<int> outer, int pos, unsigned int used){
    //this recursive call is last, and we need to check if the last element fulfills the condition
    if(pos == ringSize-1){
        //e.g. outer/2, inner/0 and inner/2 are triplets for 3-gon
        outer[ringSize-1] = tripletSum - (inner[0] + inner[ringSize-1]);
        //check if this element satisfies the unique element condition
        unsigned int currentMask = 1 << outer[ringSize-1];
        //not unique, return
        if((currentMask & used) != 0){
            return;
        }
        //first element of outer must be the smallest, else return
        //as per prob stmt, clockwise first element in outer ring should be the smallest
        //in that ring
        //for(auto x: outer)
        //    if(x < outer[0])
        //        return;
        if(outer[0]!= ringSize+1)
            return;

        //else this satisfies all the conditions, print it out
        //std::cout << "Inner:" ;
        //for(auto x: inner)
        //    std::cout << x << ",";
        //std::cout << std::endl;
        //std::cout << "Outer:" ;
        //for(auto x: outer)
        //    std::cout << x << ",";
        //std::cout << std::endl;
        //form n-gon string 
        std::string ngon ="";
        for(int i=0; i<inner.size(); i++) {
            ngon += std::to_string(outer[i]) + std::to_string(inner[i]) + std::to_string(inner[(i+1) % ringSize]);
        }
        elements.insert(ngon);
        //std::cout << ngon << std::endl;

        return ;
    }
    //for pos < ringSize-1
    //fill elements from 1 to 2*ringSize 
    for(int i=1; i<=2*ringSize; i++){
        //std::cout << "checking " << i << "for inner ring" << std::endl;
        unsigned int innerMask = 1 << i;
        if((innerMask & used)!=0)
            //i is not unique, check next i
            continue;

        unsigned int nextUsed = innerMask | used;

        inner[pos+1]=i;
        outer[pos]=tripletSum - (inner[pos] + inner[pos+1]);
        //std::cout << "checking inner:" << i << ", outer:" << outer[pos] <<  std::endl;

        //check mask
        unsigned int outerMask = 1 << outer[pos];
        if((outerMask & nextUsed)!=0)
            continue;
        //capture outerMask
        nextUsed = nextUsed | outerMask;

        //std::cout << "checking next" << std::endl;
        checkTriplet(inner, outer, pos+1, nextUsed);
    }

}

int main() {
    std::cin >> tripletSum >> ringSize; 
    tripletSum = 14;
    ringSize = 5;   //per ring size
    //divide all elements to 2 groups: inner & outer ring
    std::vector<int> inner(ringSize);
    std::vector<int> outer(ringSize);
    unsigned int allowed = 0;
    for(int i=1; i<=2*ringSize; i++)
        allowed |= 1 << i;

    //flip remaining, 0: availale, 1: used
    allowed = ~ allowed;

    //inner ring should contains 1 to ringSize and outer: ringSize+1 to 2*ringSize
    for(int i=1; i<=2*ringSize; i++) {
        //for(int i=2*ringSize; i>=1; i--) {
        //try all possible options for first element of inner and see if we can find a set that satisfies required  condittion
        inner[0]=i;
        //update allowed for this 'i'
        checkTriplet(inner, outer, 0, allowed | (1<<i));
    }
    std::cout << *elements.rbegin() << std::endl;

    return 0;
    }

