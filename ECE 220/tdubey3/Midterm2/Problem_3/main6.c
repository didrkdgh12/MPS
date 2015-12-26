#include<stdio.h>


extern int largestSubArray(int* arr, int start, int end);

int main()
{
	int test_1[]={0};
	int total=0;
	int val=-1;
	val=largestSubArray(test_1,0,0);
	if(val==0)
	{
		printf("Test Case 1: 2/2\n");
		total+=2;
	}
	else
	{
		printf("Test Case 1: 0/2\n");
	}
	fflush(stdout);
	int test_2[]={0,0,0,0,0};
	val=largestSubArray(test_2,0,4);
	if(val==0)
        {
                printf("Test Case 2: 4/4\n");
                total+=4;
        }
        else
        {
                printf("Test Case 2: 0/4\n");
        }
	fflush(stdout);
	int test_3[]={1,1,1,1,1};
	val=largestSubArray(test_3,0,4);
        if(val==0)
        {
                printf("Test Case 3: 4/4\n");
                total+=4;
        }
        else
        {
                printf("Test Case 3: 0/4\n");
        }
	fflush(stdout);
	int test_4[]={0,1,1,0,0,1,1,0,0,0,1,1,1};
	val=largestSubArray(test_4,0,12);
	if(val==6)
	{
		printf("Test Case 4: 10/10\n");
		total+=10;
	}
	else
	{
		printf("Test Case 4: 0/10\n");
	}
	fflush(stdout);
	int test_5[]={0,0,0,1,1,0,0};
	val=largestSubArray(test_5,0,6);
	if(val==4)
	{
		printf("Test Case 5: 5/5\n");
		total+=5;
	}
	else
	{
		printf("Test Case 5: 0/5\n");
	}
	printf("Total: %d/30\n",total);
	fflush(stdout);
}

