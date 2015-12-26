#include<stdio.h>


extern int largestSubArray(int* arr, int start, int end);

int main()
{
	int val=-1;
	int test_5[]={1,0,0,0,0,1,1,0,0,0};
	val=largestSubArray(test_5,0,9);
	if(val==4)
	{
		printf("Test Case 5: 5/5\n");
	}
	else
	{
		printf("Test Case 5: 0/5\n");
	}
	fflush(stdout);
}

