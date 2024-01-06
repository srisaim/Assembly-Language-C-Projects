// Testing for largest.c (Finding the largest number in an array of integers)
#include <stdio.h>

extern int largest(int arr[], int n);

int main(int argc, char **argv)
{
  int arr[] = {100, 20, 321, 5600, 45};
  int n = sizeof(arr)/sizeof(arr[0]);
  printf("The largest number in the given array is %d", largest(arr, n));
  return 0;
}

