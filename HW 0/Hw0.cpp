#include<iostream>
#include<string>
#include <vector>
using namespace std;

struct minmax {
	int min;
	int max;
	int count = 0;
};

void printarr(int A[])
{
	for (int i = 0; i < sizeof(A); i++)
	{
		cout << A[i] << " ";
	}
}

void printVector(vector<int>& A)
{
	for (int i = 0; i < A.size(); i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}

void itminmax(int A[], int n)
{
	//printing the initial array
	printarr(A);

	cout << "\n";

	int count = 0; //counts the number of comparisons made
	int min = A[0];
	int max = A[0];

	for (int i = 1; i < n; i++)
	{
		if (A[i] < min)
		{
			min = A[i];
			count++;
		}
		if (A[i] > max)
		{
			max = A[i];
			count++;
		}
	}

	cout << "The max is: " << max << "\n";
	cout << "The min is: " << min << "\n";
	cout << "The number of comparisons made on the " << n << " size array was: " << count << "\n";

}

minmax minmaxDAC(int A[], int low, int high)
{
	minmax result, left, right;
	int mid;

	//if there is only one element
	if (low == high)
	{
		result.max = A[low];
		result.min = A[low];
		return result;
	}
	//if there are two elements
	if (high == low + 1)
	{
		if (A[low] < A[high])
		{
			result.min = A[low];
			result.max = A[high];
			result.count = result.count++;
		}
		else
		{
			result.min = A[high];
			result.max = A[low];
			result.count = result.count++;
		}
	}

	mid = (low + high) / 2; //finding the mid point of the array
	left = minmaxDAC(A, low, mid); //returns the min and max from the left side of the array
	right = minmaxDAC(A, mid + 1, high);//returns the min and max from the right side of the array

	result.max = (left.max > right.max) ? left.max : right.max;
    result.count++;
	result.min = (left.min < right.min) ? left.min : right.min;
	result.count++;

	return result;
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

void insertionsort(int A[], int n)
{
	//Base Case: if there is one or less elements in the array return
	if (n <= 1)
		return;
	
	insertionsort(A, n - 1); //recursivley sort the first n-1 elements
	
	//insert last element at its correct position
	int last = A[n - 1];
	int i = n - 2;

	//move elements of A, that are greater than i, to one position ahead of their current position
	while (i >= 0 && A[i] > last)
	{
		A[i + 1] = A[i];
		i--;
	}

	A[i + 1] = last;
}

void merge(vector<int>& A, int left, int mid, int right)
{
	int n1 = mid - left + 1; //getting size of left half of vector
	int n2 = right - mid; //size of right half of vector

	vector<int> L(n1), R(n2); //creating temporary vectors

	//copying the data from each half into the temporary vectors
	for (int i = 0; i < n1; i++)
	{
		L[i] = A[left + i];
	}
	for (int j = 0; j < n2; j++)
	{
		R[j] = A[mid + 1 + j];
	}

	int i = 0, j = 0, k = left;

	//merge temp vectors back together into original vector
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = R[j];
			j++;
		}
		k++;
	}

	//copying remaining elements of L and then R into the vector
	while (i < n1)
	{
		A[k] = L[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		A[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(vector<int>& A, int left, int right)
{
	//return when the start index is greater or equal to the end index
	if (left >= right)
		return; 
	
	//spliting the vector in half
	int mid = left + (right - left) / 2;
	//calling merge sort on each half of the vector
	mergeSort(A, left, mid);
	mergeSort(A, mid + 1, right);
	merge(A, left, mid, right); //calling a function to merge the sorted pieces of the vector back together

}

int partition(int A[], int low, int high)
{
	int pivot = A[low]; //sets pivot as first element in array
	int k = high;

	for (int i = high; i > low; i--)
	{
		if (A[i] > pivot)
		{
			swap(A[i], A[k--]);
		}
	}
	swap(A[low], A[k]);
	
	return k; //returns index of pivot after partition
}

void quickSort1(int A[], int low, int high)
{
	if (low < high)
	{
		int index = partition(A, low, high); //gets the index of the pivot element at its sorted position
		quickSort1(A, low, index - 1); //recursivley calls quicksort on elements before partition
		quickSort1(A, index + 1, high); //recursivley calls quicksort on elements after parition
	}
}

int main()
{
	int A[8] = { 1,6,4,0,9,2,3,6 };

	//calling iterative minmax algorithm
	int n = sizeof(A) / sizeof(A[0]);
	itminmax(A,n);
	
	//calling divide and conquer minmax algorithm
	minmax result;
	n = sizeof(A) / sizeof(A[0]);
	result = minmaxDAC(A, 0, n - 1);
	cout << "The max is: " << result.max << "\n";
	cout << "The min is: " << result.min << "\n";
	cout << "The number of comparisons made on the " << n << " size array was: " << result.count << "\n";

	//calling recursive selection sort
	cout << "Selection Sort: " << "\n";
	selectionsort(A, 0, n);
	cout << "\n";

	//calling recurisive insertion sort
	cout << "Insertion Sort: " << "\n";
	int B[8] = { 1,6,4,0,9,2,3,6 };
	n = sizeof(B) / sizeof(B[0]);
	printarr(B);
	cout << "\n";
	insertionsort(B, n);
	printarr(B);
	cout << "\n";

	//calling recursive merge sort
	cout << "Merge Sort: " << "\n";
	vector<int> C = { 3,5,1,6,2,10,7,8 };
	printVector(C);
	n = C.size();
	mergeSort(C,0, n-1);
	printVector(C);

	//calling quick sort with fixed pivot(first element)
	cout << "Quick Sort w/Fixed Partition: " << "\n";
	int D[8] = { 3,5,1,6,2,10,7,8 };
	printarr(D);
	cout << "\n";
	n = sizeof(D) / sizeof(D[0]);
	quickSort1(D, 0, n-1);
	printarr(D);
	cout << "\n";

	return 0;
}