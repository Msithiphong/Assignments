#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

void bubble(int A[], int size);
void merge();

mutex mtx;

// IMPLEMENT GLOBAL VARIABLES
long long swapCount = 0;
long long allSwaps = 0;



int main(int argc, char* argv[])
    {
        ofstream fout;
        ifstream fin;
        int* a = new int[1000000];
        int count = 0;

        fin.open(argv[1]);
        fout.open(argv[2], ios::out | ios::trunc);
        
        

        while (fin >> a[count])
        {
            count++;
        }
        
        

        int section;
        if (string(argv[3]) != "-test")
        {
            section = count / 16;
        } else {
            section = 48 / 16;
        }

        

        
        thread t1(bubble, a + (0 * section), section); 
        thread t2(bubble, a + (1 * section), section);
        thread t3(bubble, a + (2 * section), section);
        thread t4(bubble, a + (3 * section), section);
        thread t5(bubble, a + (4 * section), section); 
        thread t6(bubble, a + (5 * section), section); 
        thread t7(bubble, a + (6 * section), section); 
        thread t8(bubble, a + (7 * section), section); 
        thread t9(bubble, a + (8 * section), section); 
        thread t10(bubble, a + (9 * section), section);
        thread t11(bubble, a + (10 * section), section);
        thread t12(bubble, a + (11 * section), section);
        thread t13(bubble, a + (12 * section), section);
        thread t14(bubble, a + (13 * section), section);
        thread t15(bubble, a + (14 * section), section);
        thread t16(bubble, a + (15 * section), count - 15 * section);

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

        
        
        for (int i = 0; i < count; i++){
            fout << a[i] << endl;
        }

       

        fout.close();
        fin.close();
        delete[] a;

        cout << count << " numbers transferred from " << argv[1] << " to " << argv[2] << endl;
        return 0;
    }


void bubble(int A[], int size)
    {
        
        mtx.lock();
        for (int i = 0; i < size - 1; i++)
            for (int j = 0; j < size - i - 1; j++)
            {
                if (A[j] > A[j + 1])
                    swap(A[j], A[j + 1]);
            }
        mtx.unlock(); 
        
       
    }

// IMPLEMENT MERGE
void merge();