#include <stdio.h>
#include <stdlib.h>

void merge_sort(int *a, int n);
void merge_recursion(int *a, int left, int right);
void merge_arrays(int *a, int left, int middle, int right);



int main()
{
    // Test case 1: Regular Case
    int array1[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int n = sizeof(array1) / 4;

    merge_sort(array1, n);
    printf("Test case 1: ");

    for (int i = 0; i < n; i++) // Output the sorted array
        printf("%d ", array1[i]);
    printf("\n");

    // Test case 2: Single element array
    int array2[] = { 5 };
    int n2 = sizeof(array2) / 4;
    merge_sort(array2, n2);
    printf("Test case 2: ");
    for (int i = 0; i < n2; i++)
        printf("%d ", array2[i]);
    printf("\n");

    // Test case 3: Already sorted array
    int array3[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int n3 = sizeof(array3) / 4;
    merge_sort(array3, n3);
    printf("Test case 3: ");
    for (int i = 0; i < n3; i++)
        printf("%d ", array3[i]);
    printf("\n");

    // Test case 4: Array with negative numbers
    int array4[] = { -22, -5, -39, -16, -8, -6, -1, -8, -9, -20 };
    int n4= 10;
    merge_sort(array4, n4);
    printf("Test case 4: ");
    for (int i = 0; i < n4; i++)
        printf("%d ", array4[i]);
    printf("\n");

    // Test case 5: Null pointer
    int *array5 = NULL;
    int n5 = 10;
    merge_sort(array5, n5);
    printf("Test case 5: Null pointer handled\n");

    return 0;

}



void merge_sort(int *a, int n) // Merge sort an array a with n elements 
{
    
    if (a == NULL || n <= 0) // Test case invalid array or negative length
        return;
    merge_recursion(a, 0, n - 1);


}

void merge_recursion(int *a, int left, int right) // Recursion to split all elements in array
{

    if (left < right)
    {
        int middle = left + (right - left) / 2;

        merge_recursion(a, left, middle);
        merge_recursion(a, middle + 1, right);

        merge_arrays(a, left, middle, right);
    }

}

void merge_arrays(int *a, int left, int middle, int right)
{

    int left_length = middle - left + 1; // Calculate length of both arrays
    int right_length = right - middle;

    int *L = (int *)malloc(left_length * sizeof(int)); // Allocate memory blocks for both arrays
    int *R = (int *)malloc(right_length * sizeof(int));

    for (int i = 0; i < left_length; i++) // Initialize new memory blocks with the 2 arrays
        L[i] = a[left + i];
    for (int j = 0; j < right_length; j++)
        R[j] = a[middle + 1 + j];

    int i = 0, j = 0, k = left; 
    while (i < left_length && j < right_length) // Begin sorting both arrays using i, j, k to
                                                // track position in the 2 arrays and original array
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < left_length)
    {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < right_length)
    {
        a[k] = R[j];
        j++;
        k++;
    }

    free(L); // Clean up the memory after finished with calculation
    free(R);

}