/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */

#include <iostream>


        template <class T>
List<T>::~List()
{
        clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
        template <class T>
void List<T>::clear()
{
        ListNode * temp = head;
        ListNode * temp2;
        while( temp != NULL){
                temp2 = temp->next;
                delete temp;
                temp = temp2;
        }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
        template <class T>
void List<T>::insertFront(T const & ndata)
{
        ListNode * newNode = new ListNode(ndata);
        if(length == 0){
                head = newNode;
                tail = newNode;
        } else {
                newNode->prev = NULL;
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
        }
        length = length + 1;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
        template <class T>
void List<T>::insertBack( const T & ndata )
{
        ListNode * newNode = new ListNode(ndata);
        if(length == 0 ){
                head = newNode;
                tail = newNode;
        }else{
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
                newNode->next=NULL;
        }
        length = length + 1;
}


/**
 * Reverses the current List.
 */
        template <class T>
void List<T>::reverse()
{
        if(head == NULL) {
                return;
        }
        reverse(head, tail);

}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
        template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
        if(startPoint == NULL) {
                return;
        }
        ListNode * current;
        ListNode * temp = NULL;
        current = endPoint;
        while(true) {
                temp = current->prev;
                current->prev = current->next;
                current->next = temp;
                if(current->next == NULL) {
                        ListNode * temp = startPoint;
                        startPoint = endPoint;
                        endPoint = temp;
                        return;
                } else {
                        current = current->next;
                }
        }
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
        template <class T>
void List<T>::reverseNth( int n )
{
        if(n >= length) {
            reverse(head, tail);
        }
        if(head == NULL && tail == NULL){
            return;
        }
        ListNode * tempA = head;
        ListNode * tempB = head;
        int i = 1;
        while(tempB != NULL){
            while(i < n-1){
                if(tempB->next != NULL){
                tempB = tempB->next;
                i++;
                }else{
                    i = n;
                }
            }
            reverse(tempA, tempB);
            if(tempB->next != NULL){
            tempB = tempA->next;
            tempA = tempB;
            }
            i = 0;
        }
}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
        template <class T>
void List<T>::waterfall()
{
        if (length==0){
                return;
        }
        ListNode* curr = head->next;
        ListNode* tempCurr = NULL;
        while(curr!=NULL&&curr->next!=NULL){
                curr->next->prev=curr->prev;
                curr->prev->next=curr->next;
                curr->prev=tail;
                tempCurr = curr->next->next;
                curr->next=NULL;
                tail->next=curr;
                tail = curr;
                curr = tempCurr;
        }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
        template <class T>
List<T> List<T>::split(int splitPoint)
{
        if (splitPoint > length)
                return List<T>();

        if (splitPoint < 0)
                splitPoint = 0;

        ListNode * secondHead = split(head, splitPoint);

        int oldLength = length;
        if (secondHead == head)
        {
                // current list is going to be empty
                head = NULL;
                tail = NULL;
                length = 0;
        }
        else
        {
                // set up current list
                tail = head;
                while (tail->next != NULL)
                        tail = tail->next;
                length = splitPoint;
        }

        // set up the returned list
        List<T> ret;
        ret.head = secondHead;
        ret.tail = secondHead;
        if (ret.tail != NULL)
        {
                while (ret.tail->next != NULL)
                        ret.tail = ret.tail->next;
        }
        ret.length = oldLength - splitPoint;
        return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
        template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{

        ListNode * current = start;
        ListNode * ret;
        for(int i = 0; i < splitPoint; i++) {
                ret = current->next;
                current = current->next;
        }
        if(current != NULL && current->prev != NULL) {
                current->prev->next = NULL; 
                current->prev = NULL;
        }
        return ret;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
        template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
        // set up the current list
        head = merge(head, otherList.head);
        tail = head;

        // make sure there is a node in the new list
        if(tail != NULL)
        {
                while (tail->next != NULL)
                        tail = tail->next;
        }
        length = length + otherList.length;

        // empty out the parameter list
        otherList.head = NULL;
        otherList.tail = NULL;
        otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
        template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
        ListNode * headFirst = first;
        ListNode * currentFirst = first;
        while(first != NULL) {   
                while(second != NULL && second->data < first->data) {   
                        ListNode * tempNode = second->next;
                        second->prev = first->prev;
                        second->next = first;
                        if(first->prev != NULL)
                                first->prev->next = second;
                        first->prev = second;
                        second = tempNode;              
                }
                currentFirst = first;
                first = first->next;
        }
        currentFirst->next = second;
        if(second != NULL) {
                second->prev = currentFirst;
        }

        while(headFirst->prev != NULL)
                headFirst = headFirst->prev;
        return headFirst;

        //    ListNode * tempfirst = first;
        // ListNode * tempsecond = second;
        // ListNode * mergehead;
        // ListNode * temp;
        // int flagfirst = 0;
        // int flagsecond = 0;
        // //int flag = 0;
        // if(first == NULL && second == NULL) {
        // 	return NULL;
        // }

        // if(tempfirst == NULL) {
        // 	return second;
        // }

        // if(tempsecond == NULL) {
        // 	return first;
        // }

        // if(tempfirst->data < tempsecond->data) {
        // 	mergehead = tempfirst;
        // 	if(tempfirst->next == NULL) {
        // 		flagfirst = 1;
        // 	}
        // 	tempfirst = tempfirst->next;
        // 	//flag = 1;
        // } else {
        // 	mergehead = tempsecond;
        // 	if(tempsecond->next == NULL) {
        // 		flagsecond = 1;
        // 	}
        // 	tempsecond = tempsecond->next;
        // 	//flag = 1;
        // }
        // temp = mergehead;
        // mergehead->prev = NULL;
        // while(flagfirst != 1 && flagsecond != 1) {
        // 	//cout << "Reched here" << endl;
        // 	if(tempfirst->data < tempsecond->data) {
        // 		//cout << "Reached here again" << endl;
        // 		temp->next = tempfirst;
        // 		temp->next->prev = temp;
        // 		temp = temp->next;
        // 		tempfirst = tempfirst->next;
        // 	}
        // 	else {
        // 		temp->next = tempsecond;
        // 		temp->next->prev = temp;
        // 		temp = temp->next;
        // 		tempsecond = tempsecond->next;
        // 	}
        // 	if(tempfirst == NULL) {
        // 		flagfirst = 1;
        // 	}
        // 	if(tempsecond == NULL) {
        // 		flagsecond = 1;
        // 	}
        // }
        // if(flagfirst == 1 && flagsecond != 1) {
        // 	while(tempsecond != NULL) {
        // 		temp->next = tempsecond;
        // 		temp->next->prev = temp;
        // 		temp = temp->next;
        // 		tempsecond = tempsecond->next;
        // 	}
        // 	flagsecond = 1;
        // }
        // else if(flagfirst != 1 && flagsecond == 1) {
        // 	while(tempfirst != NULL) {
        // 		temp->next = tempfirst;
        // 		temp->next->prev = temp;
        // 		temp = temp->next;
        // 		tempfirst = tempfirst->next;
        // 	}
        // 	flagfirst = 1;
        // }
        // if(flagfirst == 1 && flagsecond  == 1) {
        // 	temp->next = NULL;
        // }
        //    return mergehead; // change me!
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
        template <class T>
void List<T>::sort()
{
        if (empty())
                return;
        head = mergesort(head, length);
        tail = head;
        while (tail->next != NULL)
                tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
        template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
        if(chainLength <= 1) {
                return start;
        }
        ListNode * tempLeft = start;
        ListNode * tempRight = split(start, (chainLength / 2));
        start = mergesort(start, chainLength / 2);
        tempRight = mergesort(tempRight, chainLength-chainLength/2);
        start = merge(start, tempRight);
        return start;
}
