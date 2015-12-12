#include <assert.h>
#include <stdio.h>
#include "mylib.h"
#include "mysort.h"

// Display a 2D array 
void DisplayVector(char *message, int *array, int arraySize)
{
  printf("\n%s\n", message);

  int i;
  for(i = 0; i < arraySize; i++)
    {
      printf("%d\t", *(array + i));
    }
}

// From a subarray struct
int GetDataFromSubArray(SubArray subArray, int index)
{
   return *(subArray.Array.Data + subArray.StartIndex + index);
 }

// Sorts array using heapsort algorithm
void HeapSort(int *inputArray, int arrayLength)
{
    // The array on the heap must be 2^k - 1 larger than the length of the input array
    int heapArrayLength = 1;
    while(heapArrayLength <= arrayLength)
      {
	heapArrayLength *= 2;
      }
    heapArrayLength--;

    CREATEHEAP(inputHeap, heapArrayLength, arrayLength);

    // Creating a heap associated with input array
    inputHeap.Array = inputArray;

    // Creating a max heap 
    int i = (arrayLength -1) / 2;
    for(i = arrayLength; i >= 0; i--)
    {
      MaxHeapify(inputHeap, i);
    }    

    // Heap sorting
    for(i = arrayLength - 1; i > 0; i--)
      {
	int temp = *inputHeap.Array;
	*inputHeap.Array = *(inputHeap.Array + i);
	*(inputHeap.Array + i) = temp;
	inputHeap.HeapSize--;
	MaxHeapify(inputHeap, 0);
      }
}

// Recursive function 
int MergeSort(SubArray subArray)
{
  // Asserts
  assert(subArray.Array.Length > 0);
  assert(subArray.StartIndex >= 0 && subArray.StartIndex <= subArray.EndIndex);
  assert(subArray.EndIndex< subArray.Array.Length);

  if(subArray.StartIndex == subArray.EndIndex)
    {
      ProcessBaseCase(subArray);
      return 0;
    }

  int middleIndex = (subArray.StartIndex + subArray.EndIndex) / 2;

  SubArray leftSubArray = 
    { 
      .Array = subArray.Array,
      .StartIndex = subArray.StartIndex,
      .EndIndex = middleIndex
    };

  SubArray rightSubArray = 
    { 
      .Array = subArray.Array,
      .StartIndex = middleIndex + 1,
      .EndIndex = subArray.EndIndex,
    };

  MergeSort(leftSubArray);
  MergeSort(rightSubArray);
  
  Merge(leftSubArray, rightSubArray);
  
  return 0;
}

// Quicksort
void QuickSort(Array inputArray)
{
  SubArray inputSubArray = {.Array = inputArray, .StartIndex = 0, .EndIndex = inputArray.Length - 1};
  QuickSortSubArray(inputSubArray);
}

// To a subarray struct 
int SendDataToSubArray(SubArray subArray, int index, int value)
{
  *(subArray.Array.Data + subArray.StartIndex + index) = value;
  return 1;
}

// Get value to an array
int ValueFromArray(Array array, int index)
{
  return *(array.Data + index);
}

// Send value to an array
void ValueToArray(Array array, int index, int value)
{
  *(array.Data + index) = value;
}

/******************** Sub functions ********************/
// SubArrays have to be contiguous
int Merge(SubArray left, SubArray right)
{
  // printf("\n ----------Merging----------");
 
  int leftLength = left.EndIndex - left.StartIndex + 1;
  int rightLength = right.EndIndex - right.StartIndex +1;

  //  printf("\nleftLength: %d", leftLength);
  //  printf("\nrightLength: %d", rightLength);

  int sortedSubArray[leftLength + rightLength];

  int destinationIndex, leftIndex, rightIndex;
  destinationIndex = leftIndex = rightIndex = 0;

  while(leftIndex < leftLength || rightIndex < rightLength)
    {
      int valueToSend;

      if(leftIndex >= leftLength)
	{  	   
	  valueToSend = GetDataFromSubArray(right, rightIndex);
	  rightIndex++;
	}else if(rightIndex >= rightLength)
	{
	  valueToSend = GetDataFromSubArray(left, leftIndex);
	  leftIndex++;
	}else if(GetDataFromSubArray(left, leftIndex) < GetDataFromSubArray(right, rightIndex))
	{
	  valueToSend = GetDataFromSubArray(left, leftIndex);
	  leftIndex++;
	}else
	{
	  valueToSend = GetDataFromSubArray(right, rightIndex);
	  rightIndex++;
	}

      sortedSubArray[destinationIndex] = valueToSend;
      destinationIndex++;
    }

  for(destinationIndex = 0; destinationIndex < leftLength + rightLength; destinationIndex++)
    {
      *(left.Array.Data + left.StartIndex + destinationIndex) = sortedSubArray[destinationIndex];
    }
  return 0;
}

// Subroutine used in creating max heap
void MaxHeapify(Heap A, int i)
{
  int l = LEFT(i);
  int r = RIGHT(i);

  int A_i = *(A.Array + i);
  int A_l = *(A.Array + l);
  int A_r = *(A.Array + r);

  int largest = i;

  if(l < A.HeapSize && A_l > A_i)
    {
      largest = l;
    }

  if(r < A.HeapSize && A_r > *(A.Array + largest))
    {
      largest = r;
    }

  if(largest != i)
    {
      int temp;
      temp = *(A.Array + largest);
      *(A.Array + largest) = temp;
      *(A.Array + largest) = *(A.Array + i);
      *(A.Array + i) = temp;
      MaxHeapify(A, largest);
    }
}

// Partition function for QuickSort
int Partition(SubArray inputSubArray)
{
  int lowerPartitionIndex, arrayIndex;
  lowerPartitionIndex = inputSubArray.StartIndex;
  int pivot = ValueFromArray(inputSubArray.Array, inputSubArray.EndIndex);
  Array array = inputSubArray.Array;

  for(arrayIndex = inputSubArray.StartIndex; arrayIndex < inputSubArray.EndIndex; arrayIndex++)
    {
      int currentItem = ValueFromArray(array, arrayIndex);

      // Exchanging the values
      if(currentItem < pivot)
	{
	  int temp = ValueFromArray(array, lowerPartitionIndex);
	  ValueToArray(array, lowerPartitionIndex, currentItem);
	  ValueToArray(array, arrayIndex, temp);
	  lowerPartitionIndex++;
	}
    }

  // inserting pivot into proper place
  int temp = ValueFromArray(array, lowerPartitionIndex);
  ValueToArray(array, lowerPartitionIndex, pivot);
  ValueToArray(array, inputSubArray.EndIndex, temp);
  return lowerPartitionIndex;
}

// Must be a subarray with 1 element. Simply return its value
int ProcessBaseCase(SubArray subArray)
{
  assert(subArray.Array.Length > 0);
  assert(subArray.StartIndex >= 0 && subArray.StartIndex <= subArray.EndIndex);
  assert(subArray.EndIndex< subArray.Array.Length);

  return GetDataFromSubArray(subArray, subArray.StartIndex);
}

// Quicksort a sub array
void QuickSortSubArray(SubArray inputSubArray)
{
  if(inputSubArray.StartIndex >= inputSubArray.EndIndex)
    {
      return;
    }
  int pivot = Partition(inputSubArray);
  SubArray lower = {.Array = inputSubArray.Array, .StartIndex = inputSubArray.StartIndex, .EndIndex = pivot - 1};
  SubArray upper = {.Array = inputSubArray.Array, .StartIndex = pivot + 1, .EndIndex = inputSubArray.EndIndex};

  QuickSortSubArray(lower);
  QuickSortSubArray(upper);
}



