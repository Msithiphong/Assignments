#include <stdio.h>
#include <stdlib.h>

void merge_sort(int *a, int n);
void merge_recursion(int *a, int left, int right);
void merge_arrays(int *a, int left, int middle, int right);



int main()
{
    int array[] = { 8, 6, 8, 1, 3, 5, 7, 8, 1, 5 };
    int n = 10;

    merge_sort(array, n);

    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");

    return 0;

}



void merge_sort(int *a, int n) // merge sort an array a with n elements 
{


    merge(a, 0, n - 1);


}

void merge_recursion(int *a, int left, int right)
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

    int left_length = middle - left + 1; // Left portion of array
    int right_length = right - middle; // Right portion of array

    int *L = (int *)malloc(left_length * sizeof(int)); // Create memory block for left array
    int *R = (int *)malloc(right_length * sizeof(int)); // Create memory block for right array

    if (L == NULL || R == NULL) // If memory allocation failed
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Add arrays to the memory blocks

    for (int i = 0; i < left_length; i++)
    {
        L[i] = a[left + i];
    }
    for (int j = 0; j < right_length; j++)
    {
        R[j] = a[right + j];
    }


    int i, j, k;

    for (i = 0, j = 0, k = left; k <= right; k++)
    {
        if ((i < left_length) && (j >= right_length || left[&i] <= right[&j]))
        {
            a[k] = L[i];
            i++;
        } 
        else 
        {
            a[k] = R[j];
            j++;
        }
    } 


}