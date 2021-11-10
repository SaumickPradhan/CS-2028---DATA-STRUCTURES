#include "sortingalgos.h"

void Swap(int * arr, size_t index1, size_t index2){
	int tmp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = tmp;
}

void BubbleSort(int *arr, int size){
    bool have_swapped = true;
    size_t index = 0;
    int first, second;

    do {
        have_swapped = false;
        for (int i = 0; i < size - 1; ++i) {
        	first = arr[i];
			second = arr[i+1];
			if (first > second) {
				Swap(arr, i, i+1);
				have_swapped = true;
			}
		}
    } while (have_swapped); 
}