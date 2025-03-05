#include <iostream>
#include <vector>


using namespace std;

int main() {
    vector<int> nums;
    for (int i = 0; i < 4;i++)
    {
        nums.push_back(i);
    }

   



    for (int i = 0; i < nums.size(); i++)
    {
        cout << "i =  " << i << endl;
        for (int j = 0; j < nums.size(); j++)
        {
            if (i == j)
            {
                continue;
            } else 
            {
            cout << "this is j: " << j << endl;
            }
        }
    }
    return 0;
}