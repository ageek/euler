#include <iostream>
#include <vector> 

//Reciprocal cycles
//Problem 26
//
//A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:
//
//    1/2	= 	0.5
//    1/3	= 	0.(3)
//    1/4	= 	0.25
//    1/5	= 	0.2
//    1/6	= 	0.1(6)
//    1/7	= 	0.(142857)
//    1/8	= 	0.125
//    1/9	= 	0.(1)
//    1/10	= 	0.1
//
//Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.
//
//Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.
//
//I/O: (base) topo@topobox:~/myRev/cpp/euler$ ./a.out 
//982
//(base) topo@topobox:~/myRev/cpp/euler$ 
//
int periodLength(int x) {
    if(x==0) 
        return 0;
    //lest maintain a vector of all possible remainders and position where they occured
    //any re-occurence of a given remainder R will give us the period or cycle length as
    //position[first occurence] - position[2nd occurence]
    //Note : max number of remainders for a number X is X i.e. values 0, 1, 2, .... X-1 total of X nos
    //
    //lastSeen[r]=p => remainder r was last seen  at position p 
    //index of lastSeen[] is remainder
    //value of lastSeen[] is position
    //
    std::vector<int> lastSeen(x, 0);

    //first postion after decimal point
    int pos = 1;
    //initial dividend is 1, as we are doing 1/x
    int div = 1;
    while(true) {
        int r = div % x;
        // if r=0, there is no cycle, return 0
        if(r==0)
            return 0;

        // all default values are 0, anything different is a new value
        // if we already have value stored there, then its a recurrence, return diff of positions
        if(lastSeen[r] !=0) 
            return  pos - lastSeen[r];
        // else this is a new remainder, store it
        lastSeen[r] = pos;
        // 
        pos++;
        div = r * 10;
    }
}

int main() {

    // for a number X, max possible reccurence can be X-1
    int max = 1000;

    int maxSoFar = 0;
    int maxNum = 0;
    for(int i=1; i<=max; i++) {
        int t = periodLength(i);
        if (maxSoFar < t) {
            maxSoFar = t;
            maxNum = i;
        }
        //std::cout << i << " has a period=" << periodLength(i) << std::endl;
    }

        std::cout << maxNum <<  std::endl;
    return 0;
}

