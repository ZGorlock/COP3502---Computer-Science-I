//#include <stdio.h>
//#include <stdlib.h>
//
//int main()
//{
//  // Creating and initializing an array of integers
//  int unsortedData[] = { 32, 66, 75, 58, 23, 77, 85, 100, 3, 18, 36, 61, 95, 8, 14, 88, 28, 53, 39, 92, 47, 40 };
//  int sortedData[] = { 2, 6, 12, 19, 21, 27, 33, 37, 38, 41, 45, 54, 59, 62, 67, 72, 78, 84, 86, 90, 96, 100 };
//
//  // Determining the length of the array
//  int arrayLengthOne = sizeof(unsortedData) / sizeof(unsortedData[0]);
//  printf("The length of the unsorted array is %d \n", arrayLengthOne);
//
//  int arrayLengthTwo = sizeof(sortedData) / sizeof(sortedData[0]);
//  printf("The length of the sorted array is %d \n", arrayLengthTwo);
//
//  // Generating a random number between 1 and 100
//  int myNumber = rand() % 100 + 1;
//  printf("My number is %d \n", myNumber);
//
//  // Check to see if the random number is in the array
//
//  // Unsorted array check
//  int resultOne = search(unsortedData, arrayLengthOne, myNumber);
//  printf("Was the number in the unsorted array? %s\n", resultOne ? "true" : "false");
//
//  // Sorted array check
//  int resultTwo = binsearch(sortedData, arrayLengthTwo, myNumber);
//  printf("Was the number in the sorted array? %s\n", resultTwo ? "true" : "false");
//
//  // end of program
//  system("PAUSE");
//  return 0;
//}
//
//// Linear search function
//int search(int array[], int len, int value)
//{
//  int i;
//
//  printf("\n-------------\n");
//  printf("Linear search\n");
//  printf("--------------\n");
//
//  for (i = 0; i < len; i++)
//  {
//    if (array[i] == value)
//      return 1;
//
//    printf("Checked %d value(s)\n", i);
//  }
//  return 0;
//}
//
//// Binary search function
//int binsearch(int array[], int len, int value)
//{
//  int low = 0;
//  int high = len - 1;
//  int counter = 0;
//
//  printf("\n-------------\n");
//  printf("Binary search\n");
//  printf("-------------\n");
//
//  while (low <= high)
//  {
//    int mid = (low + high) / 2;
//
//    printf("The calculated middle index is %d\n", mid);
//
//    if (value < array[mid])
//      high = mid - 1;
//    else if (value > array[mid])
//      low = mid + 1;
//    else
//      return 1;
//
//    counter++;
//
//    printf("Checked %d value(s)\n", counter);
//  }
//  return 0;
//}