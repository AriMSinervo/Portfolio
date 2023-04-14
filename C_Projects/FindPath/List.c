//-------------------------------------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-------------------------------------------------------------------------------------------------------

#include "List.h" 

// structs ----------------------------------------------------------------------------------------------

//private node type
typedef struct NodeObj* Node;

//private node object
typedef struct NodeObj { 
	ListElement data;
	Node next, prev;
} NodeObj;

//private list object	
typedef struct ListObj {
	int len, index;
	Node front, back, cursor;
} ListObj;
	
// Constructors-Destructors -----------------------------------------------------------------------------

List newList(void) { //creates and returns a new, empty, list
	List list = malloc(sizeof(ListObj)); 
	assert(list != NULL);
	list->index = -1;
	list->len = 0;
	list->front = list->back = list->cursor = NULL; 
	return list; 

}

void freeList(List* pL) { //frees mem aloc'd to list and sets it to NULL
	if(pL != NULL && *pL != NULL){
		clear(*pL);
		free(*pL);
		pL = NULL;
	}
	return;
}

Node newNode(ListElement data) { //creates node for list and returns it
	Node N = malloc(sizeof(NodeObj));
	assert(N != NULL);
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return N;
}

void freeNode(Node* pN){ //frees mem aloc'd to node and set it to NULL
	if( pN!=NULL && *pN!=NULL ){
      		free(*pN);
      		*pN = NULL;
   	}
   	return;
}

// Access functions -------------------------------------------------------------------------------------

int length(List L) { //returns length of list
	if(L == NULL){
      		fprintf(stderr, "List Error: calling length() on NULL List reference\n");
      		exit(EXIT_FAILURE);
   	}
   	return L->len;
}

int index(List L) { //returns index of list cursor
	if(L == NULL){
      		fprintf(stderr, "List Error: calling index() on NULL List reference\n");
      		exit(EXIT_FAILURE);
   	}
	return L->index;
}

int front(List L) { //returns front node data if list is >0 long
	if(L == NULL) { 
		fprintf(stderr, "List Error: calling front() on NULL List reference\n");
      		exit(EXIT_FAILURE);
	}
	if(L->len == 0) {
		fprintf(stderr, "List Error: calling front() on an empty List reference\n");
      		exit(EXIT_FAILURE);
	}
	return L->front->data;

}

int back(List L) { //returns back node data if list is >0 long
	if(L == NULL) { 
		fprintf(stderr, "List Error: calling back() on NULL List reference\n");
      		exit(EXIT_FAILURE);
	}
	if(L->len == 0) {
		fprintf(stderr, "List Error: calling back() on an empty List reference\n");
      		exit(EXIT_FAILURE);
	}
	return L->back->data;
}

int get(List L) { //returns cursor data if list >0 long and cursor is set
	if(L == NULL) { 
		fprintf(stderr, "List Error: calling get() on NULL List reference\n");
      		exit(EXIT_FAILURE);
	}
	if(L->len == 0) {
		fprintf(stderr, "List Error: calling get() on an empty List reference\n");
      		exit(EXIT_FAILURE);
	}
	if(L->index == -1) {
		fprintf(stderr, "List Error: calling get() on an uninitialized index reference\n");
      		exit(EXIT_FAILURE);
	}
	return L->cursor->data;
}

bool equals(List A, List B) { //returns true if two lists are equal
	if(A == NULL || B == NULL) {
      		fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
      		exit(EXIT_FAILURE);
   	}
   	bool eq = (A->len == B->len);
   	Node N = A->front;
   	Node M = B->front;
   	while(eq && N != NULL) {
      		eq = (N->data == M->data);
      		N = N->next;
      		M = M->next;
   	}
   	return eq;
}

// Manipulation procedures ------------------------------------------------------------------------------

void clear(List L) { //removes all nodes in a list
	if(L == NULL) { 
		fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
      		exit(EXIT_FAILURE);
	}
	while(L->len) {
		deleteBack(L);
	}
	L->cursor = NULL;
	L->index = -1;
	return;
}

void set(List L, int x) { //sets cursor data if cursor is set and list is >0 long
	if(L == NULL) { 
		fprintf(stderr, "List Error: calling set() on NULL List reference\n");
      		exit(EXIT_FAILURE);
	}
	if(L->len == 0) {
		fprintf(stderr, "List Error: calling set() on an empty List reference\n");
      		exit(EXIT_FAILURE);
	}
	if(L->index == -1) {
		fprintf(stderr, "List Error: calling set() on an uninitialized index reference\n");
      		exit(EXIT_FAILURE);
	}
	L->cursor->data = x;
	return; 
}

void moveFront(List L) { //sets cursor node to front node if list >0 long
	if(L == NULL) { 
		fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
      		exit(EXIT_FAILURE);
	}
	if(L->len != 0) {
		L->cursor = L->front;
		L->index = 0;
	}
	return;
}

void moveBack(List L) { //sets cursor node to back node if list >0 long
	if(L == NULL) { 
		fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
      		exit(EXIT_FAILURE);
	}
	if(L->len != 0) {
		L->cursor = L->back;
		L->index = L->len - 1;
	}	
	return;
}

void movePrev(List L) { //moves cursor to previous node in list if list >0 long
	if(L == NULL) { 
		fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
      		exit(EXIT_FAILURE);
	}
	if(L->len == 0) {
		fprintf(stderr, "List Error: calling movePrev() on an empty List reference\n");
      		exit(EXIT_FAILURE);
	}
	if(L->index == -1) {
		return;
	}
	else if(L->index == 0) {
		L->cursor = NULL;
		L->index = -1;
		return;
	}
	else {
		Node N = L->cursor;
		L->cursor = L->cursor->prev;
		L->cursor->next = N;
		L->index -= 1;
		return;
	}
}

void moveNext(List L) { //moves cursor to next node in list if list >0 long
	if(L == NULL) { 
		fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
      		exit(EXIT_FAILURE);
	}
	if(L->len == 0) {
		fprintf(stderr, "List Error: calling moveNext() on an empty List reference\n");
      		exit(EXIT_FAILURE);
	}
	if(L->index == -1) {
		return;
	}
	else if(L->index == L->len - 1) {
		L->cursor = NULL;
		L->index = -1;
		return;
	}
	else {
		Node N = L->cursor;
		L->cursor = L->cursor->next;
		L->cursor->prev = N;
		L->index += 1;
		return;
	}
}

void prepend(List L, int x) { //adds new node with data x to front of the list
	if(L == NULL) { 
		fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
      		exit(EXIT_FAILURE);
	}
	
	Node N = newNode(x);
	
	if(L->len == 0) {
		L->front = L->back = N;
	} else {
		N->next = L->front;
		L->front->prev = N;
		L->front = N;
	}
	if(L->index != -1) {
		L->index++;
	}
	L->len++;
	return;
}

void append(List L, int x) { //adds new node with data x to back of the list
	if(L == NULL) { 
		fprintf(stderr, "List Error: calling append() on NULL List reference\n");
      		exit(EXIT_FAILURE);
	}
	
	Node N = newNode(x);
	
	if(L->len == 0) {
		L->front = L->back = N;
	} else {
		N->prev = L->back;
		L->back->next = N;
		L->back = N;
	}
	L->len++;
	return;
}

void insertBefore(List L, int x) { //adds new node with data x before cursor node if cursor is set and list >0 long
	if(L->index == -1) {
		fprintf(stderr, "List Error: calling insertBefore() on list with unitialized index\n");
      		exit(EXIT_FAILURE);
	}
	if(L == NULL){
     		fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
      		exit(EXIT_FAILURE);
   	}
   	if(L->len == 0){
      		fprintf(stderr, "List Error: calling insertBefore() on an empty List\n");
      		exit(EXIT_FAILURE);
   	}
   	Node N = newNode(x);
	N->next = L->cursor;
	N->prev = L->cursor->prev;
	if(L->cursor == L->front) {
		L->front = N;
	} else {
		L->cursor->prev->next = N;
	}
	L->cursor->prev = N;
	L->index++;
	L->len++;
	return;
}

void insertAfter(List L, int x) { //adds new node with data x after cursor node if cursor is set and list >0 long 
	if(L->index == -1) {
		fprintf(stderr, "List Error: calling insertAfter() on list with unitialized index\n");
      		exit(EXIT_FAILURE);
	}
	if(L == NULL){
     		fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
      		exit(EXIT_FAILURE);
   	}
   	if(L->len == 0){
      		fprintf(stderr, "List Error: calling insertAfter() on an empty List\n");
      		exit(EXIT_FAILURE);
   	}
    	Node N = newNode(x);
    	N->prev = L->cursor;
    	N->next = L->cursor->next;
    	if(L->cursor == L->back) {
    		L->back = N;
    	} else {
    		L->cursor->next->prev = N;
    	}
    	L->cursor->next = N;
	L->len++;
	return;
}

void deleteFront(List L) { //deletes first node in the list, makes next node the new front node
   	if(L == NULL){
     		fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
      		exit(EXIT_FAILURE);
   	}
   	if(L->len == 0){
      		fprintf(stderr, "List Error: calling deleteFront() on an empty List\n");
      		exit(EXIT_FAILURE);
   	}
   	if(L->cursor == L->front) {
   		L->cursor = NULL;
   		L->index = -1;
   	} else {
   		L->index--;
   	}
   	if(L->len > 1) {
   		Node N = L->front->next;
   		L->front->next->prev = NULL;
   		freeNode(&(L->front));
   		L->front = N;
   	} else {
   		freeNode(&(L->front));
   		L->back = L->front = NULL;
   	}
   	L->len--;
   	return;
}

void deleteBack(List L) { //deletes last node in the list, makes previous node new back node 
   	if(L == NULL){
     		fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
      		exit(EXIT_FAILURE);
   	}
   	if(L->len == 0){
      		fprintf(stderr, "List Error: calling deleteBack() on an empty List\n");
      		exit(EXIT_FAILURE);
   	}
   	if(L->cursor == L->back) {
   		L->cursor = NULL;
   		L->index = -1;
   	}
   	if(L->len > 1) {
   		Node N = L->back->prev;
   		L->back->prev->next = NULL;
   		freeNode(&(L->back));
   		L->back = N;
   	} else {
   		freeNode(&(L->back));
   		L->back = L->front = NULL;
   	}
   	L->len--;
   	return; 
} 

void delete(List L) { //deletes node pointed to by cursor
	if(L->index == -1) {
		fprintf(stderr, "List Error: calling delete() on list with unitialized index\n");
      		exit(EXIT_FAILURE);
	}
	if(L == NULL){
     		fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
      		exit(EXIT_FAILURE);
   	}
   	if(L->len == 0){
      		fprintf(stderr, "List Error: calling delete() on an empty List\n");
      		exit(EXIT_FAILURE);
   	}
   	if(L->cursor == L->front) {
   		deleteFront(L);
   		return;
   	}
   	if(L->cursor == L->back) {
   		deleteBack(L);
   		return;
   	} else {
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		L->index = -1;
		L->len--;
   		freeNode(&(L->cursor));
   		L->cursor = NULL;
   		return;
   	}
}

// Other Functions --------------------------------------------------------------------------------------

void printList(FILE* out, List L) { //prints data from list nodes sequentially (front -...-> back)
	Node N = NULL;
   	if(L == NULL) {
     		fprintf(stderr, "List Error: calling printList() on NULL List reference\n");
      		exit(EXIT_FAILURE);
   	}
   	for(N = L->front; N != NULL; N = N->next){
      		fprintf(out, "%d", N->data);
      		if(N->next != NULL) { fprintf(out, " ");}
   	}
}

List copyList(List L) { //copys list data sequentially to new list and returns it
	if(L == NULL) {
     		fprintf(stderr, "List Error: calling copyList() on NULL List reference\n");
      		exit(EXIT_FAILURE);
   	}
   	int store_index = L->index;
	List Lb = newList();
	moveFront(L);
	while(length(Lb) != length(L)) {
		append(Lb, get(L));
		moveNext(L);
	}
	moveFront(L);
	for(int i = 0; i < store_index; i++) {moveNext(L);}
	return Lb;
}

List concatList(List A, List B) {
	if(A == NULL || B == NULL) {
     		fprintf(stderr, "List Error: calling concatList() on NULL List reference\n");
      		exit(EXIT_FAILURE);
   	}
   	List Lb = copyList(A); 
   	moveFront(B);
   	while(index(B) != -1) {
   		append(Lb, get(B));
   		moveNext(B);
   	}
   	return Lb;
}
