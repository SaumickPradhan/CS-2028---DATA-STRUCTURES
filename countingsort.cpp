#include "sortingalgos.h"

#include<stdio.h>
#include<limits.h>
#include<stdlib.h>

int counting_maximum(int A[], int n){
    int max = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        if (max < A[i]){
            max = A[i];
        }
    }
    return max;
    
}

void CountingSort(int * A, int n){
    int i, j;
    // Find the maximum element in A
    int max = counting_maximum(A, n); 

    // Create the count array
    int* count = (int *) malloc((max+1)*sizeof(int));// count array of dynamic size

    // Initialize the array elements to 0
    for (i = 0; i < max+1; i++)
    {
        count[i] = 0; 
    }

    // Increment the corresponding index in the count array
    for (i = 0; i < n; i++)
    {
        count[A[i]] = count[A[i]] + 1; 
    }

    i =0; // counter for count array
    j =0; // counter for given array A

    while(i<= max){
        if(count[i]>0){
            A[j] = i;
            count[i]--;
            j++;
        }
        else{
            i++;
        }
    } 
}
