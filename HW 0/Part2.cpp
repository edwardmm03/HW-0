#include<iostream>
#include<string>
using namespace std;

void printarr(int A[])
{
	for (int i = 0; i < sizeof(A); i++)
	{
		cout << A[i] << " ";
	}
}

int minIndex(int A[], int i, int j)
{
	if (i == j)
	{
		return i;
	}

	int min = minIndex(A, i + 1, j);

	return (A[i] < A[min]) ? i : min;

}

void selectionsort(int A[], int curIndex, int n)
{
	if (curIndex == n)
	{
		//the entire array has been sorted becuase index and size are the same
		printarr(A);
		return;
	}

	int k = minIndex(A, curIndex, n - 1); //finding the index of the min
	
	if (k != curIndex)
	{
		swap(A[k], A[curIndex]);
	}

	selectionsort(A, curIndex + 1, n);
}


int main()
{
	int A[8] = { 1,6,4,0,9,2,3,6 };
	printarr(A);
	int n = sizeof(A) / sizeof(A[0]);
	//calling selection sort
	selectionsort(A,0,n);

	return 0;
}