// Name: Maxwell Sithiphong
// Class (CECS 325-02)
// Project Name (Prog 5 – Gold Rabbits)
// Due Date (11/12/2024)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <time.h>
#include <iomanip>
#include <limits>
#include <map>
#include <string>
using namespace std;


int goldRabbits(int, int); // prototype or signature

long long fiboCount;

int main()
{
    int const months = 12 * 10; // this is 10 years or 120 months
    int start = time(0);        // number of seconds since Jan 1, 1970
    int key = 0;
    for (int i = 0; i < months; i++)
    {
        
        int current = time(0);                     // number of seconds since program started
        cout << setw(5) << current - start << ":"; // print elapsed seconds
        cout << " GoldRabbits(" << setw(2) << i << ") = ";
        try {
            cout << setw(11) << goldRabbits(i, key) << "   " << "functionCalls: " << setw(4) << fiboCount << endl; // the call to goldRabbits
        } catch(const overflow_error& e) {
            cout << endl << "Overflow at fibo(" << e.what() << ")" << endl;
            goldRabbits(-1, key);
            return 0;
        }
        key++;
    }
}
// this is the goldRabbits function
int goldRabbits(int n, int key)
{   
    static map<int,int> fiboMap;
    fiboCount++;
    if (n == -1) {
        cout << "Fibo Map" << endl << "------------" << endl;
        map<int,int>::iterator it = fiboMap.begin();
        while (it != fiboMap.end()){
            cout << it->first << ":" << setw(11) << it->second << endl;
            ++it;
        }
        return 0;
    }
    else if (n == 0 || n == 1) {
        fiboMap[key] = 1;
        return 1;
    }
    else {
        fiboMap[key] = fiboMap[key - 1] + fiboMap[key - 2];
        if (fiboMap[key] < 0) {
            fiboMap.erase(key);
            throw overflow_error(to_string(key));
        }
        return fiboMap[key];     
    }
}