#include <iostream>
#include <time.h>
#include <iomanip>
#include <limits>
#include <map>
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
        cout << endl << "Overflow at fibo(" << key << ")" << endl;
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
            throw overflow_error("Integer Overflow");
        }
        return fiboMap[key];     
    }
}