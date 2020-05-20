#include <iostream>
#include <vector> 
#include <map>
#include <utility>

//Problem stmt:
//
//
//Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.
//
//How many such routes are there through a 20×20 grid?
//
//I/O:
//echo "2"|./a.out   //for 2x2 grid
//
//example
//The number of lattice paths from {\displaystyle (0,0)}(0,0) to {\displaystyle (2,3)}(2,3) is equal to {\displaystyle {\binom {2+3}{2}}={\binom {5}{2}}=10}{\binom  {2+3}{2}}={\binom  {5}{2}}=10
//short answer: 
//Lattice path for nxn square from one corner to diagonally opposite corner: C(n+k, k) 
//for (0,0) to (20,20), no of paths = C(20+20, 20)  C(40,20)= 137,846,528,820

//Note: for N=10, takes around 2sec, which is way too high -- we need to speedup
// Use dynamic proramming technique / Memoization by saving a value
// so that we dont repeat calculations for same x,y value

//global cache for speeding up recursion
std::map<std::pair<unsigned long long, unsigned long long>, unsigned long long> cache;

unsigned long long calculatePath(std::vector<std::vector<unsigned long long>> g, unsigned long long x, unsigned long long y) {
    //Memoize/ check in cache first
    auto res = cache.find(std::make_pair(x, y));
    if(res != cache.end()) {
        return res->second;
    }
    //if not in cache, calculate
    //top corner
    if(x==0 && y==0){
        return 0;
    } else if(x>=1 && y>=1) {
        unsigned long long val = calculatePath(g, x, y-1) + calculatePath(g, x-1, y) ;
        std::pair<unsigned long long,unsigned long long> point = std::make_pair(x,y);
        cache.insert(std::make_pair(point, val));
        return val;
        //edge points    
    } else if(x==0 || y==0){
        return 1;
    }
}

int main() {
    // A 2d array of size N to store the lattice points
    unsigned long long N;
    std::cin >> N; 

    //setup cache
    for(int i=0; i<N; i++) {
        cache.insert(std::make_pair(std::make_pair(i,0), 1));
        cache.insert(std::make_pair(std::make_pair(0,i), 1));
    }

    std::vector<std::vector<unsigned long long>> g(N, std::vector<unsigned long long>(N));
    g.reserve(N*N);

    //initialize the boundary edges 
    for(unsigned long long i=0; i<N; i++) {
        g[0][i]=1;
        g[i][0]=1;
    }
    std::cout << calculatePath(g, N,N) << std::endl;

    return 0;
}


