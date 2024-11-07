#include <iostream>
#include <time.h>
#include <iomanip>
#include <limits>
#include <map>
using namespace std;


int goldRabbits(int, int, map<int, int>); // prototype or signature

long long fiboCount;

int main()
{
    static map<int,int> fiboMap;
    int limit = numeric_limits<int>::max();
    int const months = 12 * 10; // this is 10 years or 120 months
    int start = time(0);        // number of seconds since Jan 1, 1970
    for (int i = 0; i < months; i++)
    {
        int current = time(0);                     // number of seconds since program started
        cout << setw(5) << current - start << ":"; // print elapsed seconds
        cout << " GoldRabbits(" << setw(2) << i << ") = ";
        try {
            cout << setw(11) << goldRabbits(i, limit, fiboMap) << endl; // the call to goldRabbits
        }
             
            catch(const overflow_error& e) {
            cout << "Printing the output" << endl;
            return 0;
        }
        
    }
}
// this is the goldRabbits function
int goldRabbits(int n, int limit, map<int, int> map)
{   
    if (n > limit) {
        throw overflow_error("Integer Overflow");
       }
    if (n == 0 || n == 1)
        return 1;
    else
        return goldRabbits(n - 1, limit, map) + goldRabbits(n - 2, limit, map);

}