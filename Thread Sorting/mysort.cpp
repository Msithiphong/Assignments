#include <iostream>
#include <thread>
#include <fstream>
#include <mutex>

using namespace std;

void bubble(int A[], int size);
void mergeAdjacent(int A[], int size);

long long swapCount;
long long allSwaps;

int main(int argc, char* argv[])
    {
        ofstream fout;
        ifstream fin;
        
        int* a = new int[1000000];


        int count = 0;

        fin.open(argv[1]);

        fout.open(argv[2], ios::out | ios::trunc);
        
        

        while (fin >> a[count]){
            count++;
        }
        
        if (argv[3] == "-test"){
            count = 10000;
        }

        int sortNum = count / 2;
        int sectionNums = count / 16;
       
        thread t1(bubble, a[0 * sectionNums], a[1 * sectionNums] - 1);
        thread t2(bubble, a[1 * sectionNums], a[2 * sectionNums] - 1);
        thread t3(bubble, a[2 * sectionNums], a[3 * sectionNums] - 1);
        thread t4(bubble, a[3 * sectionNums], a[4 * sectionNums] - 1);
        thread t5(bubble, a[4 * sectionNums], a[5 * sectionNums] - 1);
        thread t6(bubble, a[5 * sectionNums], a[6 * sectionNums] - 1);
        thread t7(bubble, a[6 * sectionNums], a[7 * sectionNums] - 1);
        thread t8(bubble, a[7 * sectionNums], a[8 * sectionNums] - 1);
        thread t9(bubble, a[8 * sectionNums], a[9 * sectionNums] - 1);
        thread t10(bubble, a[9 * sectionNums], a[10 * sectionNums] - 1);
        thread t11(bubble, a[10 * sectionNums], a[11 * sectionNums] - 1);
        thread t12(bubble, a[11 * sectionNums], a[12 * sectionNums] - 1);
        thread t13(bubble, a[12 * sectionNums], a[13 * sectionNums] - 1);
        thread t14(bubble, a[13 * sectionNums], a[14 * sectionNums] - 1);
        thread t15(bubble, a[14 * sectionNums], a[15 * sectionNums] - 1);
        thread t16(bubble, a[15 * sectionNums], a[count] - 1);

        
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();
        t7.join();
        t8.join();
        t9.join();
        t10.join();
        t11.join();
        t12.join();
        t13.join();
        t14.join();
        t15.join();
        t16.join();

        mergeAdjacent()

        for (int i = 0; i < count; i++)
        {
            fout << a[i] << endl;
        }

       

        fout.close();
        fin.close();

        cout << count << " numbers transferred from " << argv[1] << " to " << argv[2] << endl;

        delete[] a;
    }


void bubble(int A[], int start, int end)
    {
        mutex mtx;
        mtx.lock();
        for (int i = start; i < end - 1; i++)
            for (int j = start; j < end - i - 1; j++)
            {
                if (A[j] > A[j + 1])
                    swap(A[j], A[j + 1]);
                    swapCount++;
                    allSwaps++;
            }
        mtx.unlock();
    }


void mergeAdjacent(int A[], int start, int end)
{
    int mergeCount = 0;
    int* a1 = new int[62500];
    int* a2 = new int[62500];

    while (mergeCount < 16)
    {

    }
}