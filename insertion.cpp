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