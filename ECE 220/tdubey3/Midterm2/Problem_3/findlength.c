#include <stdio.h>

int largestSubArray(int* A, int start, int end);

int main()
{
        int A[]={1,0,1,1,1,1};
        int start=0,end=sizeof(A)/4-1;
        int maxsize=largestSubArray(A, start, end);
        if(maxsize==0)
        {
                printf("No subarray found\n");

        }
        else
        {
                printf("largest subarray with equal number of 0's and 1's is: %d \n",maxsize);
        }
        return 0;
}

int largestSubArray(int* arr, int start, int end)
{
	if(start == end || start > end) {
		return 0;
	}
	if( arr[start] == !arr[end]) {
		return 2 + largestSubArray(arr, start+1, end);
	} else {
		return 0 + largestSubArray(arr, start+1, end);
	}
}
