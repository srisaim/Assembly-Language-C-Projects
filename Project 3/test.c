#include <stdio.h>

int largest(int list[], int n)
   {
      int i;
      int l = list[0]; // Point to first element.

      // Notice loop starts at i = 1.
      for(i = 1; i < n; i++)
      {
         if(list[i] > l)
           l = list[i];
      }

      return l;
   }

int main(int argc, char **argv)
{
  int arr[] = {100, 20, 321, 5600, 45};
  int n = sizeof(arr)/sizeof(arr[0]);
  printf("The largest number in the given array is %d", largest(arr, n));
  return 0;
}
