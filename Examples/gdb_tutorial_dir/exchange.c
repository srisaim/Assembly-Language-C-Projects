/* C Program to exchange 2 variables
   written:  Ron Cheung
   build:  gcc -g exchange.c -o exchange
   Date: 9/9/2019
*/
#include <stdio.h>
int var1, var2, var3;

/* prototype declarations */
void exchange1(int, int);
void exchange2(int *, int *);

/* main program starts here */
void main()
{
label_0:
  printf("enter 1st variable: ");
  scanf("%d", &var1);
  printf("enter 2nd variable: ");
  scanf("%d", &var2);
label_1:
  exchange1(var1, var2);
  printf("\n after call by value function: var1= %d    var2=%d\n", var1, var2);

label_2:
  exchange2(&var1, &var2);
  printf("\n after call by reference function: var1= %d   var2=%d\n", var1, var2);
  goto label_0;
}

/* call by value function */
void exchange1(int abc1, int abc2)
{
 int temp;
 temp = abc1;
 abc1 = abc2;
 abc2 = temp;
}


/* call by reference function */
void exchange2(int *ptr1,  int *ptr2)
{
  int temp;
  temp = *ptr1;
  *ptr1 = *ptr2;
  *ptr2 = temp;
}


