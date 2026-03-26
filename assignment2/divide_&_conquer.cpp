#include <iostream>
using namespace std;


//=========================================
// TASK 1
//=========================================

//1.Binary Search

int binarySearch(int arr[], int low, int high, int target){
	if(low>high){
		return -1;
	}
	int mid = (low +high) /2;
	
	if(arr[mid]==target)
		return mid;
	else if (arr[mid] <target)
		return binarySearch(arr, mid+1, high, target);
	else
		return binarySearch(arr, low, mid-1, target);
}

//2. Merge Sort

void merge(int arr[],int low, int mid, int high){
	int n1= mid -low+1;
	int n2 =high -mid;
	
	int left[n1], right[n2];
	
	for(int i=0; i<n1; i++){
		left[i] =arr[low+i];
	}
	for(int i=0; i<n2; i++){
		right[i] = arr[mid+1+i];
	}
	
	int i =0, j=0, k=low;
	while(i<n1 && j<n2){
		if(left[i] <= right[j]){
			arr[k++] = left[i++];
		}else{
			arr[k++]= right[j++];
		}
	}
	while(i<n1){
		arr[k++] =left[i++];
	}
	while(j<n2){
		arr[k++] = right[j++];
	}
}

void mergeSort(int arr[], int low, int high){
	if(low<high){
		int mid = (low+high)/2;
		mergeSort(arr,low,mid);
		mergeSort(arr,mid+1, high);
		merge(arr, low, mid, high);
	}
}


//3.Quick Sort

int partition(int arr[], int low, int high){
	int pivot =arr[high];
	int i =low-1;
	
	for(int j=low;j<high;j++){
		if(arr[j]<=pivot){
			i++;
			swap(arr[i],arr[j]);
		}
	}
	swap(arr[i+1],arr[high]);
	return i+1;
}

void quickSort(int arr[], int low, int high){
	if(low< high){
		int pi =partition(arr, low, high);
		quickSort(arr,low,pi-1);
		quickSort(arr,pi+1, high);
	}
}


//4.Find Max and Min

struct MinMax{
	int min,max;
};

MinMax findMinMax(int arr[], int low, int high){
	MinMax result, left, right;
	
	//if array has only single element
	if(low==high){
		result.min =arr[low];
		result.max=arr[low];
		return result;
	}
	
	// If array has two elements
	if(high == low+1){
		if(arr[low] < arr[high]){
			result.min =arr[low];
			result.max =arr[high];
		}else{
			result.min =arr[high];
			result.max = arr[low];
		}
		
		return result;
	}
	
	// If array has more than two elements
	int mid =(low+high)/2;
	left = findMinMax(arr,low,mid);
	right =findMinMax(arr,mid+1,high);
	
	result.min =(left.min < right.min) ? left.min : right.min;
	result.max =(left.max > right.max) ? left.max: right.max;
	
	return result;
	
}


//5.Strassen's Matrix Multiplication

//ADD two 2X2 matrices
void matAdd(int A[2][2], int B[2][2],int C[2][2]){
	for(int i =0; i<2; i++){
		for(int j=0; j<2; j++){
		C[i][j] = A[i][j] + B[i][j];
		}
	}
}

//SUBTRACT two 2X2 matrices
void matSub(int A[2][2], int B[2][2],int C[2][2]){
	for(int i =0; i<2; i++){
		for(int j=0; j<2; j++){
		C[i][j] = A[i][j] - B[i][j];
		}
	}
}

void strassen(int A[2][2], int B[2][2], int C[2][2]) {
    int M1 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
    int M2 = (A[1][0] + A[1][1]) *  B[0][0];
    int M3 =  A[0][0]            * (B[0][1] - B[1][1]);
    int M4 =  A[1][1]            * (B[1][0] - B[0][0]);
    int M5 = (A[0][0] + A[0][1]) *  B[1][1];
    int M6 = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1]);  
    int M7 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]); 

    C[0][0] = M1 + M4 - M5 + M7;
    C[0][1] = M3 + M5;
    C[1][0] = M2 + M4;
    C[1][1] = M1 - M2 + M3 + M6;
}

//Normal matrix multiplication:
void matMultiply(int A[2][2], int B[2][2], int C[2][2]){
	for(int i =0;i<2;i++){
		for(int j=0;j<2;j++){
			C[i][j] =0;
			for(int k =0;k<2;k++){
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

//functions to print array
void printArray(int arr[], int n) {
    printf("  [ ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("]\n");
}

void print2x2(int M[2][2], const char* name) {
    printf("  %s:\n", name);
    for (int i = 0; i < 2; i++)
        printf("    [ %d  %d ]\n", M[i][0], M[i][1]);
}


// MAIN

int main() {

    // 1. Binary Search 
    printf("  \n1. BINARY SEARCH\n\n");
    

    int bs[] = {2, 5, 8, 12, 16, 23, 38, 45, 67, 90};
    int n    = 10;
    int target = 23;

    printf("  Array  : "); printArray(bs, n);
    printf("  Target : %d\n", target);

    int idx = binarySearch(bs, 0, n - 1, target);
    if (idx != -1)
        printf("  Found %d at index %d\n", target, idx);
    else
        printf("  %d not found\n", target);

    // 2. Merge Sort 
    
    printf(" \n 2. MERGE SORT\n\n");
    
    int ms[] = {38, 27, 43, 3, 9, 82, 10};
    int ms_n = 7;

    printf("  Before : "); printArray(ms, ms_n);
    mergeSort(ms, 0, ms_n - 1);
    printf("  After  : "); printArray(ms, ms_n);

    //  3. Quick Sort 
    printf(" \n 3. QUICK SORT\n\n");
    
    int qs[] = {64, 25, 12, 22, 11, 90, 42};
    int qs_n = 7;

    printf("  Before : "); printArray(qs, qs_n);
    quickSort(qs, 0, qs_n - 1);
    printf("  After  : "); printArray(qs, qs_n);

    // 4. Max & Min
    printf(" \n 4. FIND MAX & MIN (Divide and Conquer)\n\n");

    int mm[]  = {70, 250, 35, 18, 99, 4, 150, 63};
    int mm_n  = 8;

    printf("  Array  : "); printArray(mm, mm_n);

    MinMax res = findMinMax(mm, 0, mm_n - 1);
    printf("  Max    : %d\n", res.max);
    printf("  Min    : %d\n", res.min);

    // 5. Strassen 
    printf(" \n 5. STRASSEN'S MATRIX MULTIPLICATION (2x2)\n\n");
   

    int A[2][2] = {{1, 2}, {3, 4}};
    int B[2][2] = {{5, 6}, {7, 8}};
    int CS[2][2], CN[2][2];

    strassen(A, B, CS);
    matMultiply(A,B,CN);

    print2x2(A,  "Matrix A");
    print2x2(B,  "Matrix B");
    print2x2(CS, "Strassen Result");
    print2x2(CN, "Normal   Result");

    printf("\n  Both results match: %s\n",
        (CS[0][0]==CN[0][0] && CS[0][1]==CN[0][1] &&
         CS[1][0]==CN[1][0] && CS[1][1]==CN[1][1]) ? "YES" : "NO");

    printf("================================================\n");
    return 0;
}


