#include <iostream>
#include <vector> 
#include <map>

//Counting Sundays
//Problem 19
//
//You are given the following information, but you may prefer to do some research for yourself.
//
//    1 Jan 1900 was a Monday.
//    Thirty days has September,
//    April, June and November.
//    All the rest have thirty-one,
//    Saving February alone,
//    Which has twenty-eight, rain or shine.
//    And on leap years, twenty-nine.
//    A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
//
//How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
//
//I/O:
//(base) topo@topobox:~/myRev/cpp/euler$ echo "2000 12 31"|./a.out
//171
//(base) topo@topobox:~/myRev/cpp/euler$

bool isLeap(int );
int whichDay(int year, int month, int day) ;

// we need to find out if 1st day of month is sunday, so default day=1
int whichDay(int year, int month, int day=1) {
    // days per month
    int days[] ={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int totalDaysUptoLastYear = 0;
    //upto previous year
    int y;
    for(y=1900; y<year; y++) {
        totalDaysUptoLastYear += 365;
        if (isLeap(y))
            totalDaysUptoLastYear += 1;
    }
    //for this year till the given month
    int daysUpToMonth=0;
    for(int i=1; i < month; i++) {
        if(i==2 && isLeap(year))
            daysUpToMonth +=  29;
        else 
            daysUpToMonth += days[i];

    }
    //1 Jan 1900 was a Monday. i.e. 1st was Monday
    //1,8,15,22 etc will be Monday
    //
    //dayOfWeek - day
    //1- Monday
    //2- Tuesday
    //3- Wednesday
    //4 -Thursday
    //5- Friday
    //6- Saturday
    //0- Sunday
    //
    int dayOfWeek = (totalDaysUptoLastYear+ daysUpToMonth + day) % 7;
    return dayOfWeek;
}

bool isLeap(int year) {
    bool isLeap = false;
    if(year%100==0) {
        if(year %400==0)
            isLeap = true;
    } else if(year %4==0) {
        isLeap = true;
    }
    return isLeap;
}

int main() {
    int yr,month,day;
    std::cin >>yr>>month>>day;

    int totalSundays=0;
    for(int i=1901; i<=2000; i++) {
        for(int j=1; j<=12; j++) {
            //1-Monday
            //2-Tue
            //..
            //0-Sunday
            if(0 == whichDay(i, j))
                totalSundays++;
        }
    }

    std::cout << totalSundays << std::endl;
    return 0;
}

