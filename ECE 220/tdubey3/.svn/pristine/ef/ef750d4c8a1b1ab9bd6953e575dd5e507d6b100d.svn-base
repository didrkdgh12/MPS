//Problem covering Array Manipulation and Functions

void reverseArray(int* inArray, int len, int* outArray);
int insertArray(int* inArray, int len, int* subArray, int subLen, int position);
int isInArray(int* inArray, int len, int* subArray, int subLen);

/*function reverseArray
 *INPUT: 
 *inArray- integer array inArray of length len
 *len- length of array inArray and outArray, greater than 0
 *OUTPUT:
 *outArray- integer array outArray of length len, has already been initalized for you
 *RETURN: none
 *This function reverses the order of the elements in inArray and stores them in the array outArray.
 *As an example, if inArray contains the elements 1,2,3,4,5
 *then this function sets the values of outArray to 5,4,3,2,1
 */
void reverseArray(int* inArray, int len, int* outArray){
	int i;
	int j = 0;
	for(i = len-1; i >= 0; i--) {
		outArray[j] = inArray[i];
		j++;
	}
}

/*function insertArray
 *INPUT: 
 *inArray- integer array inArray of length len
 *len- length of array inArray, greater than 0
 *subArray- integer array of length subLen
 *subLen- length of array subArray, greater than 0 and <=len
 *position- desired starting location of the subArray in the array (assume value is between 0 and len-1)
 *OUTPUT:
 *Alters the values of inArray starting at the index position, writing the values of subArray into inArray.
 *RETURN: 0 if position+subLen>len, 1 otherwise
 *If the position is valid, this function inserts the values of subArray into inArray starting at the index position. 
 *The values of inArray should be overwritten with the values of subArray. 
 *Be sure to check if the position and lengths are valid, as described in the return value. 
 *If position+subLen>len, do not alter inArray.
 *As an example, if subArray = [2,3,4], inArray = [6,7,8,9,10], and position=2, the value of inArray after the function
 *should be inArray = [6,7,2,3,4]
 *In this case, if position=3, then the function should return 0 and not change inArray. 
 */
int insertArray(int* inArray, int len, int* subArray, int subLen, int position){
	if(!((position + subLen) > len)) {
		int i;
		for(i = 0; i < subLen; i++){
			inArray[i+position] = subArray[i];
		}
		return 1;
	}
	return 0;
}


/*function isInArray
 *INPUT: 
 *inArray- integer array inArray of length len
 *len- length of array inArray, greater than 0
 *subArray- integer array of length subLen
 *subLen- length of array subArray, greater than 0 and <=len
 *RETURN: if all the values of subArray appear in inArray in order, returns the index of the start of subArray, otherwise -1
 *You may assume subArray occurs at most once in the inArray.
 *As an example, if inArray contains the elements 1,2,3,4,5
 *and subArray the elements 3,4
 *it should return 2
 *If inArray contains 1,2,3,4,5 and subArray 4,3, it should return -1
 */
int isInArray(int* inArray, int len, int* subArray, int subLen){
	int index = -1;
	int i, j;
	int numFound = 0;
	for(i = 0; i <= len - subLen; i++) {
		for(j = 0; j < subLen; j++) {
			if(inArray[i+j] == subArray[j]){
				numFound++;
			}
		}
		if(numFound == subLen){
			index = i;
			return index;
		} else {
			numFound = 0;
		}
	}
	return index;
}

