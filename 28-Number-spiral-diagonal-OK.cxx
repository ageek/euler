#include <iostream>
#include <vector> 

//Number spiral diagonals
//Problem 28
//
//Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:
//
//21 22 23 24 25
//20  7  8  9 10
//19  6  1  2 11
//18  5  4  3 12
//17 16 15 14 13
//
//It can be verified that the sum of the numbers on the diagonals is 101.
//
//What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?
//
//
//core algo: 
//1. base =1 for layer/level =1 (the innnermost element)
//2. layer=2 onwards, we need to find the first element(dependent on the last element of last layer) and the remaining
//   3 are equidistant, delta  of which is dependent on the layer no
//3. for each layer, find the 1st, 1st+delta, 1st+2*delta, 1st+3*delta and sum up ...till max layer=10001
//I/O: echo 1001 |./a.out

int main() {
    int maxLayer;
    std::cin >> maxLayer; 

    //Layers:
    // for our algo, its 1,2,3.....
    // but for the problem, size is 1x1, 3x3, 5x5 , so adapt it to our algo
    //
    maxLayer = 1+(maxLayer/2);

    // base layer 
    int layer =1;
    // base element of spiral path
    int last  =1;
    //base sum
    int sum =1;

    //loop over from layer 2 till maxLayer
    for(layer=2; layer <= maxLayer; layer++) {
        //to add 4 elements
        int n=3;
        //delta between each corner elements
        int delta = 2*(layer-1);

        while(n-- >= 0) {
            int current = delta + last;
            sum += current;
            //save last 
            last = current;
        }
    }

    std::cout << sum << std::endl;
    return 0;
}

