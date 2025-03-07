#include <iostream>
using namespace std;


void merge(int A[], int B[], int *merge[], int size){
    cout << *A << endl;
    cout << *B << endl;
    //try and figure out how to get first element of A into merge
    
    //for (int i = 0; i < size; i++) *merge[i] = A[i];
    //for (int i = 0; i < size; i++) cout << *merge[i] << endl;
}
int main (){
    int a[] = {4,3,2,1,6,7,8,9};
    int size = sizeof(a) / sizeof(int);
    int sectionSize = size / 2;
    int* mergeList = new int[8];

    merge(a + 0, a + 4, &mergeList, size);
    
    //for (int i = 0; i < size; i++) cout << mergeList[i] << endl;

}
