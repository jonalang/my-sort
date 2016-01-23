#ifndef _MY_SORT_
#define _MY_SORT_

// Represents an array. An array must be initialized. 
// Put a pointer to it in the struct, and store its length
typedef struct
{
  int Length;
  int *Data;
}Array;

// Represents a subarray of another array. 
typedef struct
{
  Array Array;
  int StartIndex;
  int EndIndex;
}SubArray;

// Heap data structure
typedef struct Heap{
  int *Array;
  int ArrayLength;
  int HeapSize;
}Heap;

// Operations on heap data structure
#define LEFT(i) (i) * 2 + 1;
#define RIGHT(i) (i) * 2 + 2;
#define PARENT(i) (i - 1) / 2;
#define CREATEHEAP(heapName, _arrayLength, _heapSize) int heapName##Data[(_arrayLength)]; Heap heapName = {.Array = heapName##Data, .ArrayLength = _arrayLength, .HeapSize = _heapSize}
#define CREATEARRAY(arrayName, _arrayLength) int arrayName##Data[(_arrayLength)]; Array arrayName = {.Data = arrayName##Data, .Length = (_arrayLength)}

void DisplayVector(char *message, int *array, int arraySize);
int *GenerateRandomArray(int *initializedSpace, int arrayLength, int min, int max);
int GetDataFromSubArray(SubArray subArray, int index);
int Merge(SubArray left, SubArray right);
int MergeSort(SubArray subArray);
void HeapSort(int *inputArray, int arrayLength);
void MaxHeapify(Heap inputHeap, int i);
int Partition(SubArray inputSubArray);
int ProcessBaseCase(SubArray subArray);
void QuickSort(Array inputArray);
void QuickSortSubArray(SubArray inputSubArray);
int SendDataToSubArray(SubArray subArray, int index, int value);
int ValueFromArray(Array array, int index);
void ValueToArray(Array array, int index, int value);

#endif
