#include<stdio.h>
#include<stdlib.h>

typedef struct stack STACK;

struct stack{
 
 void *data;
 
 int count;
 
 STACK *link;
};


STACK *createStack()
{
 STACK *stackHead;
 
 stackHead=(STACK *)malloc(sizeof(STACK));
 
 stackHead->link==NULL;
 
 stackHead->count=0;
 
 return stackHead;
}  


STACK *push(STACK *stackHead, void *i)
{
 STACK *pNew;
 
 if(stackHead->count==0)
 {
 	stackHead->data=i;
 	++stackHead->count;
 	
 	return stackHead;
 	
 }
 
 
 else
 {
 		pNew=(STACK *)malloc(sizeof(STACK));
 		
 		pNew->count=stackHead->count + 1;
 		pNew->data=i;
 		
 		pNew->link=stackHead;
 		stackHead=pNew;
 		
 		return stackHead;
 }
} 		


void *pop(STACK **stackHead)
{
 STACK *dltPtr;
 void *popped;
 
 if((*stackHead)->count==0)
 {
 	popped=NULL;
 	
 	return popped;
 }
 
 if((*stackHead)->count==1)
 {
 	popped=(*stackHead)->data;
 		 
 	--(*stackHead)->count;
 	
 	return popped;
 	
 }
 
 else
 {
 	dltPtr=*stackHead;
 	
	popped=dltPtr->data;
	
	*stackHead=dltPtr->link;
	
	free(dltPtr);
	
	return popped;
	
 }
} 			 


void *stackTop(STACK *stackHead)
{
 if(stackHead->count==0)
 {
 	//printf("STACK IS EMPTY!\n");
 	
 	return NULL;
 }
 
 
 else
 	return stackHead->data;
} 		 


int stackEmpty(STACK *stackHead)
{
 if(stackHead->count==0)
 	return 1;
 	
 else
 	return 0;
} 		


int stackCount(STACK *stackHead)
{
 return stackHead->count;
}


STACK *destroyStack(STACK *stackHead)
{
 STACK *dltPtr;
 
 if(stackHead->count==0)
 {
 	free(stackHead);
 	
 	return stackHead;
 }	
 	
 else
 {
 	while(stackHead->count!=1)
 	{
 		dltPtr=stackHead;
 		
 		stackHead=dltPtr->link;
 		
 		free(dltPtr);
 	}
 	
 	
 	free(stackHead);
 	
 	return stackHead;
 }
} 
