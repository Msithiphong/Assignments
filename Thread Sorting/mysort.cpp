#include <iostream>
#include <thread>
#include <fstream>

using namespace std;

void bubble(int A[], int size);


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
       
        thread t1(bubble, a, sortNum);
        thread t2(bubble, a, sortNum);
        thread t3(bubble, a, sortNum);
        thread t4(bubble, a, sortNum);
        thread t5(bubble, a, sortNum);
        thread t6(bubble, a, sortNum);
        thread t7(bubble, a, sortNum);
        thread t8(bubble, a, sortNum);
        thread t9(bubble, a, sortNum);
        thread t10(bubble, a, sortNum);
        thread t11(bubble, a, sortNum);
        thread t12(bubble, a, sortNum);
        thread t13(bubble, a, sortNum);
        thread t14(bubble, a, sortNum);
        thread t15(bubble, a, sortNum);
        thread t16(bubble, a, sortNum);

        
        for (int i = 0; i < count; i++){
            fout << a[i] << endl;
            
        }

       

        fout.close();
        fin.close();

        cout << count << " numbers transferred from " << argv[1] << " to " << argv[2] << endl;
    }


void bubble(int A[], int size)
    {
        for (int i = 0; i < size - 1; i++)
            for (int j = 0; j < size - i - 1; j++)
            {
                if (A[j] > A[j + 1])
                    swap(A[j], A[j + 1]);
            }
    }

