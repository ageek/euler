#include <iostream>
#include <vector> 
//Problem stmt:
//
//Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.
//
//How many such routes are there through a 20×20 grid?
//
//I/O:
//echo "2"|./a.out   //for 2x2 grid
//
//example
//short answer: 
//Lattice path for nxn square from one corner to diagonally opposite corner: C(n+k, k) 
//for (0,0) to (20,20), no of paths = C(20+20, 20)  C(40,20)= 137,846,528,820

//Note: for N=10, takes around 2sec, which is way too high -- we need to speedup
int calculatePath(std::vector<std::vector<int>> g, int x, int y) {
    //top corner
    if(x==0 && y==0){
        return 0;
    } else if(x>=1 && y>=1) {
        return calculatePath(g, x, y-1) + calculatePath(g, x-1, y) ;
    
   //edge points    
    } else if(x==0 || y==0){
        return 1;
    }
}

int main() {

    // A 2d array of size N to store the lattice points
    int N;
    std::cin >> N; 

    std::vector<std::vector<int>> g(N, std::vector<int>(N));
    g.reserve(N*N);

    //initialize the boundary edges 
    for(int i=0; i<N; i++) {
        g[0][i]=1;
        g[i][0]=1;
    }

    std::cout << calculatePath(g, N,N) << std::endl;

    return 0;
}


