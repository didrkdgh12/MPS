//Test File For Midterm 2 Problem
//Provides tests for each function

#include <stdio.h>

#include "arrays.c"

int main(){
    int i;
    
    //Test 1 for reverseArray
    int inArray1_1[5]={1,2,3,4,5};
    int outArray1_1[5]={0,0,0,0,0};
    printf("reverseArray, Test 1\n");
    printf("inArray before: ");
    for(i=0;i<5;i++){
        printf("%d ",inArray1_1[i]);
    }
    reverseArray(inArray1_1,5,outArray1_1);
    printf("\noutArray after: ");
    for(i=0;i<5;i++){
        printf("%d ",outArray1_1[i]);
    }
    printf("\n");
    //Test 2 for reverseArray
    int inArray1_2[1]={1};
    int outArray1_2[1]={0};
    printf("\nreverseArray, Test 2\n");
    printf("inArray before: ");
    for(i=0;i<1;i++){
        printf("%d ",inArray1_2[i]);
    }
    reverseArray(inArray1_2,1,outArray1_2);
    printf("\noutArray after: ");
    for(i=0;i<1;i++){
        printf("%d ",outArray1_2[i]);
    }
    printf("\n");
    //Test 1 for insertArray
    int inArray2_1[5]={1,2,3,4,5};
    int subArray2_1[3]={7,8,9};
    int position = 2;
    printf("\ninsertArray, Test 1, Position=%d\n",position);
    printf("inArray before: ");
    for(i=0;i<5;i++){
        printf("%d ",inArray2_1[i]);
    }
    printf(" subArray: ");
    for(i=0;i<3;i++){
        printf("%d ",subArray2_1[i]);
    }
    int returnVal = insertArray(inArray2_1,5,subArray2_1,3,position);
    printf("\ninArray after: ");
    for(i=0;i<5;i++){
        printf("%d ",inArray2_1[i]);
    }
    printf("\nReturn Val: %d \n",returnVal);    
    
    //Test 2 for insertArray
    int inArray2_2[5]={1,2,3,4,5};
    int subArray2_2[3]={7,8,9};
    position = 4;
    printf("\ninsertArray, Test 2, Position=%d\n",position);
    printf("inArray before: ");
    for(i=0;i<5;i++){
        printf("%d ",inArray2_2[i]);
    }
    printf(" subArray: ");
    for(i=0;i<3;i++){
        printf("%d ",subArray2_2[i]);
    }
    returnVal = insertArray(inArray2_2,5,subArray2_2,3,position);
    printf("\ninArray after: ");
    for(i=0;i<5;i++){
        printf("%d ",inArray2_2[i]);
    }
    printf("\nReturn Val: %d \n",returnVal);

    //Test 1 for isInArray
    int inArray3_1[5]={1,2,3,4,5};
    int subArray3_1[3]={3,8,9};
    int positionOut;
    printf("\nisInArray, Test 1\n");
    printf("inArray: ");
    for(i=0;i<5;i++){
        printf("%d ",inArray3_1[i]);
    }    
    printf(" subArray: ");
    for(i=0;i<3;i++){
        printf("%d ",subArray3_1[i]);
    }
    positionOut = isInArray(inArray3_1,5,subArray3_1,3);
    printf("\nReturn Value: %d \n",positionOut);    
     
    //Test 2 for isInArray
    int inArray3_2[5]={1,2,3,4,5};
    int subArray3_2[2]={3,4};
    printf("\nisInArray, Test 2\n");
    printf("inArray: ");
    for(i=0;i<5;i++){
        printf("%d ",inArray3_2[i]);
    }
    printf(" subArray: ");
    for(i=0;i<2;i++){
        printf("%d ",subArray3_2[i]);
    }
    positionOut = isInArray(inArray3_2,5,subArray3_2,2);
    printf("\nReturn Value: %d \n",positionOut);    
     
    return 0;
}
