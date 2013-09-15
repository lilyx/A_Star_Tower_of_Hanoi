#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "List.h"

//initialize the start state
struct node* ini(int n){
	struct node* node=(struct node*)malloc(sizeof(struct node));
	node->left=(int*)malloc(n*sizeof(int));
	int i;
	for(i=0;i<n;i++){
		node->left[i]=i+1;
	}
	node->leftSize=n;
	node->middle=NULL;
	node->middleSize=0;
	node->right=NULL;
	node->rightSize=0;
	node->depth=0;
	node->h=-1;
	return node;
}

//generate a new state
struct node* newNode(int* left, int* middle, int* right,int depth,int leftSize,int middleSize, int rightSize){
	struct node* node=(struct node*)malloc(sizeof(struct node));
	if(left!=NULL){
		node->left=(int*)malloc(leftSize*sizeof(int));
		memcpy(node->left, left,leftSize*sizeof(int));
	}else node->left=NULL;
	if(middle!=NULL){
		node->middle=(int*)malloc(middleSize*sizeof(int));
		memcpy(node->middle, middle,middleSize*sizeof(int));
	}else node->middle=NULL;
	if(right!=NULL){
		node->right=(int*)malloc(rightSize*sizeof(int));
		memcpy(node->right, right,rightSize*sizeof(int));
	}else node->right=NULL;
 
 	node->leftSize=leftSize;
	node->middleSize=middleSize;
	node->rightSize=rightSize;
	node->depth=depth;
	node->h=node_h(node);
	return node;
	
}

//generate a new list node
struct list* newList(struct node* start, struct node* prev, int disk, int to){

	struct list* list=(struct list*)malloc(sizeof(struct list));
	
	if(start!=NULL){
		list->node=newNode(start->left, start->middle, start->right,start->depth,start->leftSize,start->middleSize,start->rightSize);
	 }else list->node=NULL;
	
	if(prev!=NULL){
		list->prev=newNode(prev->left,prev->middle,prev->right,prev->depth,prev->leftSize,prev->middleSize,prev->rightSize);
	}else list->prev=NULL;
	
	list->disk=disk;
	list->toPole=to;
	list->next=NULL;

	return list;
}

/*return the node's heuristic value,return the total number of disks of left
 *and middle poles pulse the twice number of disks that 
 *in the right pole and smaller than disks that in left 
 *or middle poles
 */ 
int node_h(struct node* node){
	
	int h=0;
	int leftMax=0;
	int middleMax=0;
	if(node->leftSize!=0&&node->middleSize!=0){
		h=node->leftSize+node->middleSize;
		leftMax=node->left[node->leftSize-1];
		middleMax=node->middle[node->middleSize-1];
	}else if(node->leftSize!=0){
		h=node->leftSize;
		leftMax=node->left[node->leftSize-1];
	}else if(node->middleSize!=0){
		h=node->middleSize;
		middleMax=node->middle[node->middleSize-1];
	}
	
	for(int i=0;i<node->rightSize;i++){
		if(node->right[i]<middleMax||node->right[i]<leftMax)
			h +=2;
	}
	
	return h;
	
}

//check if the list contain final goal, and if yes, return the list node that have the goal
struct list* contain_goal(struct list* list,int n){

	if(list==NULL)
		return NULL;
		
	struct node* node=(struct node*)malloc(sizeof(struct node));

	node->right=(int*)malloc(n*sizeof(int));
	int i;
	for(i=0;i<n;i++){
		node->right[i]=i+1;
	}
	node->middle=NULL;
	node->left=NULL;
	node->rightSize=n;
	node->middleSize=0;
	node->leftSize=0;

	struct list* p=list;

	while(p!=NULL){
		if(compareNode(p->node,node)){
			return p;
		}
		p=p->next;
	}
	return NULL;
}

//move the first number of array1 to the first position of array2
void move(int** array1, int** array2,int size1,int size2){

  	int* old1=*array1;
  	int* old2=*array2;

  	*array1=(int*)calloc((size1-1),sizeof(int));
  	*array2=(int*)calloc((size2+1),sizeof(int));
  	
  	
  	for(int i=0;i<size1-1;i++){
		(*array1)[i]=old1[i+1];
	}
	
	(*array2)[0]=old1[0];
	for(int j=1;j<size2+1;j++){
		(*array2)[j]=old2[j-1];
	}
	
}

//return the list node that contain "node"
struct list* getList(struct list* list, struct node* node){
	if(list==NULL){
		return NULL;
	}		
	struct list* p=list;
	while(p!=NULL){
		if(compareNode(p->node,node)==1){
			return p;
		}
		p=p->next;
	}
	
	return NULL;
}

//check if "node" in the list
int contain(struct list* list, struct node* node){
	if(list==NULL){
		return 0;
	}
		
	struct list* p=list;
	int i=0;
	while(p!=NULL){
		if(compareNode(p->node,node)==1){
			i=1;
			if(p->node->depth>node->depth){
				p->node->depth=node->depth;
				i=2;
			}
			return i;
		}
		p=p->next;
	}
	
	return i;
}

//compare if n1==n2
int compareNode(struct node* n1, struct node* n2){

	if(n1->leftSize!=n2->leftSize||n1->middleSize!=n2->middleSize||n1->rightSize!=n2->rightSize)
		return 0;
	
	for(int i=0;i<n1->leftSize;i++){
			if(n1->left[i]!=n2->left[i])
				return 0;
	}
	for(int i=0;i<n1->middleSize;i++){
			if(n1->middle[i]!=n2->middle[i])
				return 0;
	}
	for(int i=0;i<n1->rightSize;i++){
			if(n1->right[i]!=n2->right[i])
				return 0;
	}
	
	return 1;
}

//remove a node from list
void removeFromList(struct list** list, struct node* node){
	struct list* p=*list;
	if(compareNode(p->node,node)==1){
		*list=p->next;
		freeNode(&p->node);
		freeNode(&p->prev);
		free(p);
		p=NULL;
		return;
	}
		
	int i=0;
	while(p->next!=NULL){
		if(compareNode(p->next->node,node)==1){
			i=1;
			break;
		}
		p=p->next;
	}
	if(i==1){
		struct list* temp=p->next;
		p->next=p->next->next;
		freeNode(&temp->node);
		freeNode(&temp->prev);
		free(temp);
		temp=NULL;
	}
}

//add a new list node to the end of list
void append(struct list** list, struct list* ll){

	if(contain(*list, ll->node)!=0)
		return;
		
	if(*list==NULL){
		*list=newList(ll->node,ll->prev,ll->disk,ll->toPole);
		return;
	}
	
	struct list* l=*list;
	while(l->next!=NULL){
		l=l->next;
	}
	l->next=newList(ll->node,ll->prev,ll->disk,ll->toPole);	
	
}

//move the node that has the minimum f(x)=g(x)+h(x) value in "from" list to list "to"
void moveNodes(struct list** from, struct list** to){

	struct list* p=*from;
	struct list* move=newList(p->node,p->prev,p->disk,p->toPole);
	int value=p->node->h+p->node->depth;
	p=p->next;

	while(p!=NULL){
		int fValue=p->node->h+p->node->depth;
		if(fValue==value){
			append(&move,p);
		}else if(fValue<value&&move!=NULL){
			deleteList(&move);
			move=newList(p->node,p->prev,p->disk,p->toPole);
			value=fValue;
		}
		p=p->next;
	}
	struct list* temp=move;
	while(temp!=NULL){
		append(to, temp);
		removeFromList(from,temp->node);
		temp=temp->next;
	}
}

//delete node
void freeNode(struct node** node){
	if(*node==NULL)
		return;
	struct node* p=*node;
	if(p->left!=NULL)
		free(p->left);
	if(p->middle!=NULL)
		free(p->middle);
	if(p->right!=NULL)
		free(p->right);
	free(p);
	*node=NULL;
}

//delete list
void deleteList(struct list** list){
	struct list* p=*list;
	while(p!=NULL){
		struct list* pp=p;
		p=p->next;
		freeNode(&pp->node);
		freeNode(&pp->prev);
		free(pp);
	}
	*list=NULL;
}


