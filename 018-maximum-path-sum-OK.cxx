#include <iostream>
#include <vector> 
#include <algorithm>

//Maximum path sum I
//Problem 18
//
//By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.
//
//   3
//  7 4
// 2 4 6
//8 5 9 3
//
//That is, 3 + 7 + 4 + 9 = 23.
//
//Find the maximum total from top to bottom of the triangle below:
//
//                   75
//                  95 64
//                 17 47 82
//                18 35 87 10
//               20 04 82 47 65
//              19 01 23 75 03 34
//             88 02 77 73 07 63 67
//            99 65 04 28 06 16 70 92
//          41 41 26 56 83 40 80 70 33
//        41 48 72 33 47 32 37 16 94 29
//       53 71 44 65 25 43 91 52 97 51 14
//     70 11 33 28 77 73 17 78 39 68 17 57
//   91 71 52 38 17 14 91 43 58 50 27 29 48
// 63 66 04 68 89 53 67 30 73 16 69 87 40 31
//04 62 98 27 23 09 70 98 73 93 38 53 60 04 23
//
//NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route. 
//However, Problem 67, is the same challenge with a triangle containing one-hundred rows; it cannot be solved by brute force, and requires a clever method! ;o)
//
//I/O:
//echo "4 3 7 4 2 4 6 8 5 9 3"|./a.out
//
//convert input data to single row format using: 
//$ awk 1 ORS=' ' 18input.txt
//topo@topobox:~/myRev/cpp/euler$ echo "15 75 95 64 17 47 82 18 35 87 10 20 04 82 47 65 19 01 23 75 03 34 88 02 77 73 07 63 67 99 65 04 28 06 16 70 92 41 41 26 56 83 40 80 70 33 41 48 72 33 47 32 37 16 94 29 53 71 44 65 25 43 91 52 97 51 14 70 11 33 28 77 73 17 78 39 68 17 57 91 71 52 38 17 14 91 43 58 50 27 29 48 63 66 04 68 89 53 67 30 73 16 69 87 40 31 04 62 98 27 23 09 70 98 73 93 38 53 60 04 23" |./a.out
//1074
//(base) topo@topobox:~/myRev/cpp/euler$
//
//Similarly test the same code for Prob67 as well using data in 67input.txt

int main() {
    //input rows
    int N;
    std::cin >> N; 

    // maintains a running max for each element, max(parentleft, parentright)
    std::vector<int> last(1);
    std::cin >> last[0];

    //core algo:
    //maintain two vectors, both running
    //last -    contains the parent elements (set to 1st parent to start with)
    //current - read stdin and calculate max sums for each element using last's data, 
    //          and keep copying over current to last, before fresh caculation of current is done


    //    1
    //  2  3
    //4  5   6
    //
    //is stored as below:
    //
    //1
    // 2 3
    // 4 5 6
    //
    // so leftparent(5)  =2   i.e. if(j>0) last[j-1]
    // and rightparent(5)=3   i.e  if(j<last.size()) last[j]
    // i - row
    // j - col
    for(int i=1; i<N; i++) {
        std::vector<int> current;
        // ith row has i+1 no of elements, with i>=1
        for(int j=0; j<i+1; j++) {
            //read a num
            int x;
            std::cin >>x;

            // and process and save before reading the next num
            //
            // check if we have left & right parents
            // leftparent
            int leftParent =0; 
            if(j>0) {
                leftParent = last[j-1];
            }

            int rightParent = 0;
            if(j<last.size()){
                rightParent = last[j];
            }
            //pick max (leftParent, rightParent)
            int sum = x + std::max(leftParent, rightParent);
            //std::cout << leftParent << "  " << rightParent << ", sum=" << sum << std::endl;
            current.push_back(sum);
        }
        //copy over curret to last, before current gets calculated afresh
        last = current;
    }


    //when loop gets over, we have all the final sums stored in last, pick the max as final result
    // directly pick the max or min , max_element returs an iterator, use * to get the value
    // https://stackoverflow.com/questions/6570139/mingw-error-min-is-not-a-member-of-std
    std::cout << *std::max_element(last.begin(), last.end()) << std::endl;

    return 0;
}

