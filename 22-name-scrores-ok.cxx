#include <iostream>
#include <vector> 
#include <set>
#include <map>


//
//Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.
//
//For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.
//
//What is the total of all the name scores in the file?

std::string readOneWord() {
    std::string word;
    while(true) {
        char c= std::cin.get();

        //no more input
        if(!std::cin)
            break;
        if(c =='"')
            continue;
        //end of this word
        if(c == ',')
            break;
        word += c;
    }
//    std::cout << word << " "; 
    return word;
}

int main() {

    // set ensures data is always in sorted order
    std::set<std::string> names;

    while(true) {
        std::string current = readOneWord();
        if(current.empty())
            break;
        names.insert(current);
    }
    //now the names are sorted, store in a map to keep track of position of each name
    std::map<std::string, int> sortedNames;
    //for storing position of each name
    int x=1;
    for(auto a: names) {
        sortedNames[a] = x++;
    }

    unsigned long long sum = 0;
    // loop through all items in map and calculate their value * position, sum up for all
    for(auto a: sortedNames ) {
        int val =0;
        for(auto x: a.first) {
            // A -> 1
            // B -> 2
            val += x - 'A' +1;
            std::cout << x << "="<< x - 'A' +1 << "  ";
        }
        int p = a.second;
        sum += val * p;
//        std::cout << a.first << "," << a.second << "=" << val*p << std::endl;
    }

    std::cout << sum << std::endl;

    return 0;
}

