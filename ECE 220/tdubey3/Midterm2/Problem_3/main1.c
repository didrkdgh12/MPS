#include<stdio.h>


extern int largestSubArray(int* arr, int start, int end);

int main()
{
	int test_1[]={0};
	int val=-1;
	val=largestSubArray(test_1,0,0);
	if(val==0)
	{
		printf("Test Case 1: 5/5\n");
	}
	else
	{
		printf("Test Case 1: 0/5\n");
	}
	fflush(stdout);
	return 0;
}

