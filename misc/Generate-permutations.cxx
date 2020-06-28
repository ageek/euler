#include <iostream>

void permute(std::string str, int l, int r) {
    //reached the end node of permutation tree, print
    if(l==r)
        std::cout << str << std::endl;
    else {
        for(int i=l; i<=r; i++) {
            //swap
            std::swap(str[i], str[l]);
            permute(str, l+1, r);
            //backtrack last swap
            std::swap(str[i], str[l]);
        }
    }
}

int main() {
    std::string input="123";
    permute(input, 0,input.size()-1);
    return 0;
}

