// Name: Ruben Calderon
// CruzID: rucalder
//  Assignment Name: pa5


#include<stdio.h>
#include<stdlib.h>
#include"List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
	int data;
	struct NodeObj* next;
	struct NodeObj* prev;
	} NodeObj;

// private Node type
typedef NodeObj* Node;

typedef struct ListObj{
	Node first;
	Node last;
	Node cursor;
	int cursorIndex;
	int length;
} ListObj;

typedef ListObj* List;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = N->prev = NULL;
	return(N);
}

//freeNode()
// Frees heap memory pointed to be *pN, sets *pN to NULL
// private
void freeNode(Node* pN){
	if(pN != NULL && *pN!=NULL){
		free(*pN);
		*pN = NULL;
	}
}

// newList()
// Returns reference to new empty Queue object.
List newList(void){
	List L;
	L = malloc(sizeof(ListObj));
	L->first = L->last = L->cursor = NULL;
	L->length = 0;
	L->cursorIndex = -1;
	return(L);
}

// freeList()
// frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.S
void freeList(List* pL){
	if(pL!=NULL && *pL!=NULL){
		while(length(*pL) != 0){
			deleteFront(*pL);
		}
		free(*pL);
		*pL=NULL;
	}
}

// Access functions -----------------------------------------------------------

// getFront()
// Returns the value at the front of Q.
// Pre: !isEmpty(Q)
int front(List L){
	if(L == NULL){
		printf("List Error: calling front() on an empty List\n");
		exit(1);
	}
	return(L->first->data);
}

int back(List L){
        if(L == NULL){
                printf("List Error: calling back() on an empty List\n");
                exit(1);
        }
        return(L->last->data);
}

//getLength()
// Returns the length of L
int length(List L){
	if(L==NULL){
		printf("List Error: calling length() on NULL List reference\n");
		exit(1);
	}
	return(L->length);
}

// index()
// Returns index of cursor element if defined, -1 otherwise
int index(List L){
	if(L == NULL){
		printf("List Error: calling index() on an empty List\n");
                exit(1);
	}
	if(L->cursor == NULL){
		return(-1);
	}
	return(L->cursorIndex);
}

// get(List L)
// returns cursor element of L
int get(List L){
	if(L == NULL || L->length == 0 || L->cursorIndex < 0){
		printf("List Error: calling get() on a NULL reference\n");
		exit(1);
	}
	return(L->cursor->data);
}

// equals()
// returns true(1) iff LIsts A and B are in same state, returns false(0) otherwise
int equals(List A, List B){
        if(A == NULL || B == NULL){
                printf("List Error: calling equals() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
	
	if(A->length != B->length){
		return(0);
	}

	Node tempA = A->first;
	Node tempB = B->first;
	

	while(tempA != NULL && tempB != NULL){
		if(tempA == NULL || tempB == NULL){
			return(0);
		}
		if(tempA != NULL || tempB != NULL){
			if((tempA->data != tempB->data)){
				return(0);
			}
		}
		tempA = tempA->next;
		tempB = tempB->next;
	}
	return(1);
}

//isEmpty()
// Returns true(1) if Q is empty, otherwise returns false(0)
int isEmpty(List L){
	if(L == NULL){
		printf("List Error: calling isEmpty() on NULL List reference\n");
		exit(1);
	}
	return(L->length == 0);
}

// Manipulation procedures ----------------------------------------------------
// clear()
// Resets L to its original empty state
void clear(List L){
	if(L == NULL){
                printf("List Error: calling clear() on NULL List reference\n");
                exit(1);
        }
	while(length(L) != 0){
		deleteFront(L);
	}
}

// moveFront(List L)
// If L is non-empty, sets cursor under the front element, otherwise, do nothing
void moveFront(List L){
	if(L == NULL){
                printf("List Error: calling moveFront() on NULL List reference\n");
                exit(1);
        }
	if(!(isEmpty(L))){
		L->cursor = L->first;
		L->cursor->next = L->first->next;
		L->cursorIndex = 0;
	}
}

// moveBack(List L)
// If L is non-empty, sets cursor under the back element, otherwise do nothing
void moveBack(List L){
	if(L == NULL){
                printf("List Error: calling moveBack() on NULL List reference\n");
                exit(1);
        }
	if(!(isEmpty(L))){
		L->cursor = L->last;
		L->cursor->prev = L->last->prev;
		L->cursorIndex = length(L) - 1;
	}
}

//movePrev(List L)
// If cursor is defined and not at front, move cursor one step toward the front of L; if cursor is defined and at front, cursor becomes undefined; if cursor is undefined do nothing
void movePrev(List L){
	if(L == NULL){
                printf("List Error: calling movePrev() on NULL List reference\n");
                exit(1);
        }
	if(L->cursorIndex > 0){
		L->cursor = L->cursor->prev;
		L->cursorIndex--;
	}
	else if(L->cursorIndex == 0){
		L->cursor = NULL;
		L->cursorIndex = -1;
	}
}

//moveNext(List L)
// If cursor is defined and not at back, move cursor one step toward the back of L; if cursor isdefined and at back, cursor becomes undefined; if cursor is undefined do nothing
void moveNext(List L){
	if(L == NULL){
                printf("List Error: calling moveNext() on NULL List reference\n");
                exit(1);
 	}       
	if(L->cursorIndex == L->length-1){
		L->cursor = NULL;
		L->cursorIndex = -1;
	}
	else if(L->cursorIndex >= 0){
                L->cursor = L->cursor->next;
                L->cursorIndex++;
        }
}

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int data){
	if(L == NULL){
                printf("List Error: calling prepend() on NULL List reference\n");
                exit(1);
        }
	if(L->length > 0){
		Node N = newNode(data);
		N->next = L->first;
		L->first->prev = N;
		L->first = N;
		if(L->cursorIndex != -1){
			L->cursorIndex++;
		}
	}
	else{
		Node N = newNode(data);
		L->first = L->last = N;
	}
	L->length++;
}

// append()
// Insert new element into L.If L is non-empty,insertion takes place after back element.
void append(List L, int data){
	if(L == NULL){
                printf("List Error: calling append() on NULL List reference\n");
                exit(1);
        }
	if(L->length > 0){
		Node N = newNode(data);
		N->prev = L->last;
		L->last->next = N;
		L->last = N;
	}
	else{
		Node N = newNode(data);
		L->first = L->last = N;
	}
	L->length++;
}

//insertBefore()
//Insert new element before cursor.
//Pre: length()>0, index()>=0
void insertBefore(List L, int data){
	if(L == NULL){
		printf("List Error: calling insertBefore() on NULL List reference\n");
                exit(1);
        }
	if(isEmpty(L)){
		printf("List Error: calling insertBefore() on empty List\n");
                exit(1);
        }
	if(L->cursorIndex == -1){
		printf("List Error: calling insertBefore() on invalid cursor\n");
                exit(1);
        }
	else if(L->cursor != NULL && L->cursor->prev != NULL){
		Node N = newNode(data);
		N->prev = L->cursor->prev;
		L->cursor->prev->next = N;
		L->cursor->prev = N;
		N->next = L->cursor;
	}
	else if(L->cursor == L->first){
		Node N = newNode(data);
		L->first->prev = N;
		N->next = L->first;
		L->first = N;
	}
	L->cursorIndex++;
	L->length++;
}

//insertAfter()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
	if(L == NULL){
                printf("List Error: calling insertAfter() on NULL List reference\n");
                exit(1);
        }
	if(isEmpty(L)){
                printf("List Error: calling insertAfter() on empty List\n");
                exit(1);
        }
	if(L->cursorIndex == -1){
                printf("List Error: calling insertAfter() on invalid cursor\n");
                exit(1);
        }
	else if(L->cursor != NULL && L->cursor->next != NULL){
		Node N = newNode(data);
		N->next = L->cursor->next;
		L->cursor->next->prev = N;
		N->prev = L->cursor;
		L->cursor->next = N;
	}
	else if(L->cursor == L->last){
		Node N = newNode(data);
		L->last->next = N;
		N->prev = L->last;
		L->last = N;
	}
	L->length++;
}

//deleteFront(List L)
// Delete the front element. Pre: length()>0
void deleteFront(List L){
	if(L == NULL){
                printf("List Error: calling deleteFront() on NULL List reference\n");
                exit(1);
        }
        if(isEmpty(L)){
                printf("List Error: calling deleteFront() on empty List\n");
                exit(1);
        }
	Node N = L->first;
	if(L->cursor == L->first){
		movePrev(L);
	}
	if(L->first == L->last){
		L->first = L->last = NULL;
	}
	else{
		L->first = L->first->next;
		N->next = NULL;
		L->first->prev = NULL;
	}
	L->length--;
	freeNode(&N);
	if(L->cursorIndex != -1){
		L->cursorIndex--;
	}
}

// deleteBack(List L)
// Delete the back element. Pre: length()>0
void deleteBack(List L){
	if(L == NULL){
                printf("List Error: calling deleteBack() on NULL List reference\n");
                exit(1);
        }
        if(isEmpty(L)){
                printf("List Error: calling deleteBack() on empty List\n");
                exit(1);
        }
	Node N = L->last;
	if(L->cursor == L->last){
		moveNext(L);
	}
	if(L->first == L->last){
                L->first = L->last = NULL;
        }
	else{
		L->last = L->last->prev;
		L->last->next = NULL;
		N->prev = NULL;
	}
	L->length--;
	freeNode(&N);
}

// delete()
// Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete(List L){
	if(L == NULL){
                printf("List Error: calling delete() on NULL List reference\n");
                exit(1);
        }
        if(isEmpty(L)){
                printf("List Error: calling delete() on empty List\n");
                exit(1);
        }
        if(L->cursorIndex == -1){
                printf("List Error: calling delete() on invalid cursor\n");
                exit(1);
        }
	if(L->cursor == L->first){
		deleteFront(L);
	}
	else if(L->cursor == L->last){
		deleteBack(L);
	}
	else{
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		Node N = L->cursor;
		freeNode(&N);
		L->length--;
	}	
}

// printList()
// Prints to the file pointed to by out, a string representation of L consisting of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L){
	if(L == NULL){
                printf("List Error: calling printList() on NULL List reference\n");
                exit(1);
        }
	Node N = L->first;
	while(N!=NULL){
		if(index(L) != length(L) - 1){
			fprintf(out, "%d ", N->data);
		}
		else{
			fprintf(out, "%d", N->data);
		}
		N = N->next;
	}
	//fprintf(out, "%s\n", "");
}

// copyList(List L)
// Returns a new List representing the same integer sequence as L. The cursor in the new list is undefined, regardless of the state of the cursor in L. The state of L is unchanged.
List copyList(List L){
	if(L == NULL){
                printf("List Error: calling copyList() on NULL List reference\n");
                exit(1);
        }
	List new = newList();
	Node N = L->first;
	while(N!=NULL){
		append(new, N->data);
		N = N->next;
	}
	return(new);
}

//concatList()
// Returns a new List which is the concatenation of A and B. The cursor in the new List is undefined, regardless of the states of the cursors in A and B. The states of A and B are unchanged.
List concatList(List A, List B){
	if(A == NULL || B == NULL){
		printf("List Error: calling concatList() on NULL List reference\n");
                exit(1);
        }
	Node N = A->first;
	List new = newList();
	while(N!=NULL){
		append(new, N->data);
		N=N->next;
	}
	N = B->first;
	while(N!=NULL){
		append(new, N->data);
		N=N->next;
	}
	return(new);
}
