#include "sortingalgos.h"
//Insertion sort compares a temp value to items in the array and sorts accordingly
void InsertionSort(int arr[], int size){ //ALEX
  int j;
  int curr;
  for(int i =1; i < size; ++i){
    curr = arr[i];
    j = i-1;
    while(j >= 0 && curr < arr[j]){ //flip the < or > operator to go in descending order for curr vs. arr[j]
      arr[j+1] = arr[j];
      --j;
    }
    arr[j+1] = curr;
  }
}