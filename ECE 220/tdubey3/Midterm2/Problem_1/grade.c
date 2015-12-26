//Test File For Midterm 2 Problem
//Provides tests for each function

#include <stdio.h>

#include "arrays.c"

int testRemoveArray(int* inArray,int len,int* outArray,int* goldOutArray,int testNum)
{
    int i;
    printf("reverseArray, Test %d  ",testNum);
    printf("inArray before: ");
    for(i=0;i<len;i++){
        printf("%d ",inArray[i]);
    }
    reverseArray(inArray,len,outArray);
    printf("\noutArray student: ");
    for(i=0;i<len;i++){
        printf("%d ",outArray[i]);
    }
    printf("  outArray gold: ");
    for(i=0;i<len;i++){
        printf("%d ",goldOutArray[i]);
    }
    int flag = 1;
    for (i=0;i<len;i++){
        if(outArray[i]!=goldOutArray[i]){
            flag = 0;
        }
    }    
    if(flag==1){
        printf("  Test %d Correct",testNum);
        printf("\n");
        return 1;
    }

    printf("  Test %d InCorrect",testNum);
    printf("\n");
    return 0;
    
}

int testInsertArray(int* inArray,int len,int* subArray, int subLen,int* goldOutArray,int testNum,int position,int returnGold)
{
    int i;
    printf("\ninsertArray, Test %d, Position=%d  ",testNum,position);
    printf("inArray before: ");
    for(i=0;i<len;i++){
        printf("%d ",inArray[i]);
    }
    printf(" subArray: ");
    for(i=0;i<subLen;i++){
        printf("%d ",subArray[i]);
    }
    int returnVal = insertArray(inArray,len,subArray,subLen,position);
//    int returnValGold = 1;
    printf("\ninArray after (student): ");
    for(i=0;i<len;i++){
        printf("%d ",inArray[i]);
    }
    printf("  inArray after (gold): ");
    for(i=0;i<len;i++){
        printf("%d ",goldOutArray[i]);
    }
    printf("\n return value student: %d  return value gold: %d",returnVal,returnGold);
    int flag = 1;
    for (i=0;i<len;i++){
        if(inArray[i]!=goldOutArray[i]){
            flag = 0;
        }
    }
    if((returnVal==0 && returnGold!=0)||(returnVal!=0 && returnGold==0)){//Check if return value is not zero, some students were confused, so we'll accept any value that is not zero
        flag=0;}    
    if(flag==1){
        printf("  Test %d Correct",testNum);
	return 1;
    }
    printf("  Test %d InCorrect",testNum);
    return 0;
    
    
}

int testIsInArray(int* inArray, int len, int* subArray, int subLen,int testNum, int returnGold){
    int positionOut,i;
    printf("\nisInArray, Test %d ",testNum);
    printf(" inArray: ");
    for(i=0;i<len;i++){
        printf("%d ",inArray[i]);
    }    
    printf(" subArray: ");
    for(i=0;i<subLen;i++){
        printf("%d ",subArray[i]);
    }
    positionOut = isInArray(inArray,len,subArray,subLen);
    printf("\nReturn Value Student: %d Return Value Gold: %d",positionOut,returnGold);    
    if(positionOut==returnGold){
        printf("  Test %d Correct",testNum);
        return 1;
    }
    printf("  Test %d Incorrect",testNum);
    return 0;
}

int main(){
    //int i;
    
    //Test 1 for reverseArray
    int pass = 0;
    int inArray1_1[5]={1,2,3,4,5};
    int outArray1_1[5]={0,0,0,0,0};
    int goldOutArray1_1[5]={5,4,3,2,1};
    pass = pass+testRemoveArray(inArray1_1,5,outArray1_1,goldOutArray1_1,1);
    //Test 2 for reverseArray
    int inArray1_2[1]={1};
    int outArray1_2[1]={0};
    int goldOutArray1_2[1]={1};
    pass = pass+testRemoveArray(inArray1_2,1,outArray1_2,goldOutArray1_2,2);
    //Test 3 for reverseArray
    int inArray1_3[4]={1,2,3,4};
    int outArray1_3[4]={0,0,0,0};
    int goldOutArray1_3[4]={4,3,2,1};
    pass = pass+testRemoveArray(inArray1_3,4,outArray1_3,goldOutArray1_3,3);
    //Test 4 for reverseArray
    int inArray1_4[7]={1,2,3,4,5,6,7};
    int outArray1_4[7]={0,0,0,0,0,0,0};
    int goldOutArray1_4[7]={7,6,5,4,3,2,1};
    pass = pass+testRemoveArray(inArray1_4,7,outArray1_4,goldOutArray1_4,4);
    printf("*****reverseArray passed %d/4 cases*****\n",pass);
    
    //Test 1 for insertArray
    pass = 0;
    int inArray2_1[5]={1,2,3,4,5};
    int subArray2_1[3]={7,8,9};
    int goldArray2_1[5]={1,2,7,8,9};
    int position = 2;
    pass=pass+testInsertArray(inArray2_1,5,subArray2_1,3,goldArray2_1,1,position,1);
    
    //Test 2 for insertArray
    int inArray2_2[5]={1,2,3,4,5};
    int subArray2_2[3]={7,8,9};
    int goldArray2_2[5]={1,2,3,4,5};
    position = 4;
    pass=pass+testInsertArray(inArray2_2,5,subArray2_2,3,goldArray2_2,2,position,0);
    //Test 3 for insertArray
    int inArray2_3[5]={1,2,3,4,5};
    int subArray2_3[1]={7};
    int goldArray2_3[5]={1,2,3,4,7};
    position = 4;
    pass=pass+testInsertArray(inArray2_3,5,subArray2_3,1,goldArray2_3,3,position,1);

    //Test 4 for insertArray
    int inArray2_4[5]={1,2,3,4,5};
    int subArray2_4[3]={6,7,8};
    position = 0;
    int goldArray2_4[5]={6,7,8,4,5};
    pass=pass+testInsertArray(inArray2_4,5,subArray2_4,3,goldArray2_4,4,position,1);
    printf("\n*****insertArray passed %d/4 cases***** \n",pass);
    
    //Test 1 for isInArray
    pass = 0;
    int inArray3_1[5]={1,2,3,4,5};
    int subArray3_1[3]={3,8,9};
    pass=pass+testIsInArray(inArray3_1, 5, subArray3_1, 3, 1 , -1);
    //Test 2 for isInArray
    int inArray3_2[5]={1,2,3,4,5};
    int subArray3_2[2]={3,4};
    pass=pass+testIsInArray(inArray3_2, 5, subArray3_2, 2, 2 , 2);
    
    //Test 3 for isInArray
    int inArray3_3[5]={1,2,3,4,5};
    int subArray3_3[1]={3};
    pass=pass+testIsInArray(inArray3_3, 5, subArray3_3, 1, 3 , 2);
    
    //Test 4 for isInArray
    int inArray3_4[5]={1,2,3,4,5};
    int subArray3_4[2]={4,3};
    pass=pass+testIsInArray(inArray3_4, 5, subArray3_4, 2, 4 , -1);
    printf("\n*****isInArray passed %d/4 cases*****\n \n",pass);
    
    return 0;
}
