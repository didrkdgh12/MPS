#include<stdio.h>


extern int largestSubArray(int* arr, int start, int end);

int main()
{
	int val=-1;
	int test_4[]={0,1,1,0,0,1,1,0,0,0,1,1,1};
	val=largestSubArray(test_4,0,12);
	if(val==12)
	{
		printf("Test Case 4: 5/5\n");
	}
	else
	{
		printf("Test Case 4: 0/5\n");
	}
	fflush(stdout);
}

