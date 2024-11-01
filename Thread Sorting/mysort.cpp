#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;

void bubble(int A[], int size, int processNumber);
void merge(int A[], int B[], int size, int result[]);

mutex mtx;

// IMPLEMENT GLOBAL VARIABLES
long long swapCount[16] = {0};


int main(int argc, char* argv[]) {
    ofstream fout;
    ifstream fin;
    int* a = new int[1000000];
    int count = 0;

    fin.open(argv[1]);
    fout.open(argv[2], ios::out | ios::trunc);

    while (fin >> a[count]) {
        count++;
    }


    int section;
    section = count / 16;
    
    if (argv[3]) {
        section = 10000 / 16;
    } else {
        section = count / 16;
    }

    
    // Create threads for bubble sort
    
    
    thread t1(bubble, a + (0 * section), section, 0); 
    thread t2(bubble, a + (1 * section), section, 1); 
    thread t3(bubble, a + (2 * section), section, 2); 
    thread t4(bubble, a + (3 * section), section, 3); 
    thread t5(bubble, a + (4 * section), section, 4); 
    thread t6(bubble, a + (5 * section), section, 5); 
    thread t7(bubble, a + (6 * section), section, 6); 
    thread t8(bubble, a + (7 * section), section, 7); 
    thread t9(bubble, a + (8 * section), section, 8); 
    thread t10(bubble, a + (9 * section), section, 9); 
    thread t11(bubble, a + (10 * section), section, 10); 
    thread t12(bubble, a + (11 * section), section, 11); 
    thread t13(bubble, a + (12 * section), section, 12); 
    thread t14(bubble, a + (13 * section), section, 13); 
    thread t15(bubble, a + (14 * section), section, 14); 
    thread t16(bubble, a + (15 * section), section, 15); 
    
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

    
    // Print total swaps
    long long totalSwaps = 0;
    for (int i = 0; i < 16; i++){
        totalSwaps += swapCount[i];
    }
    cout << "Total Swaps: " << totalSwaps << endl;
    

    // Dynamically allocate merge list
    int* mergedList = new int[count];
    int nums = section * 16;
    for (int size = section; size < nums; size *= 2) {
        for (int i = 0; i < nums; i += 2 * size) {
            merge(a + i, a + i + size, (i + 2 * size > nums) ? nums - i : 2 * size, mergedList + i);
        }
        swap(a, mergedList);
    }

    

    // Output sorted array to file
    for (int i = 0; i < count; i++) {
        fout << a[i] << endl;
    }

    // Close files and delete dynamically allocated arrays
    fout.close();
    fin.close();
    delete[] a;
    delete[] mergedList;
    
    return 0;
}

void bubble(int A[], int size, int processNumber) {
    
    long long swaps = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                swap(A[j], A[j + 1]);
                swaps++;

            }
        }
    }
    mtx.lock();
    swapCount[processNumber] = swaps;
    cout << "Process " << processNumber + 1 << " swap count: " << swapCount[processNumber] << endl;
    mtx.unlock();
}

void merge(int a[], int b[], int size, int list[]) {
    int i = 0, j = 0, k = 0;
    while (i < size / 2 && j < size / 2) {
        if (a[i] < b[j]) {
            list[k++] = a[i++];
        } else {
            list[k++] = b[j++];
        }
    }
    while (i < size / 2) {
        list[k++] = a[i++];
    }
    while (j < size / 2) {
        list[k++] = b[j++];
    }
}
