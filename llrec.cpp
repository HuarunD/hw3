#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************


void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
	smaller = nullptr;
	larger = nullptr;
	if(head == nullptr){

	}
	else if(head->val>pivot){
		larger = head;
		head = head->next;
		llpivot(head,smaller,larger->next,pivot);

	}
	else if(head->val<=pivot){
		smaller = head;
		head = head->next;
		llpivot(head,smaller->next,larger,pivot);
	}
}