#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "List.h"

int N;					//the number of disks
struct list* open=NULL; //the state that could get to
struct list* close=NULL;//the state that after take movement

void expand(struct node* node){
	//initialize the three pole
	int* left=NULL;
	int* right=NULL;
	int* middle=NULL;
	if(node->left!=NULL){
		left=(int*)malloc(node->leftSize*sizeof(int));
		memcpy(left, node->left, node->leftSize*sizeof(int));
	}
	if(node->right!=NULL){
		right=(int*)malloc(node->rightSize*sizeof(int));
		memcpy(right, node->right, node->rightSize*sizeof(int));
	}
	if(node->middle!=NULL){
		middle=(int*)malloc(node->middleSize*sizeof(int));
		memcpy(middle, node->middle, node->middleSize*sizeof(int));
	}
	
	/*following found all the movement that the current state could take
	 *then take the movement, then append the state after movement to list 
	 *"open".
	 */
	if(node->leftSize!=0 && (node->middle==0||middle[0]>left[0])){
		move(&left,&middle,node->leftSize, node->middleSize);
		struct node* n=newNode(left,middle,right,node->depth+1,node->leftSize-1,node->middleSize+1, node->rightSize);
		
		free(left);
		free(middle);
		if(node->leftSize!=0){
			left=(int*)calloc(node->leftSize,sizeof(int));
			memcpy(left, node->left, node->leftSize*sizeof(int));
		}else left=NULL;
		if(node->middleSize!=0){
			middle=(int*)calloc(node->middleSize,sizeof(int));
			memcpy(middle, node->middle, node->middleSize*sizeof(int));
 		}else middle=NULL;
 		
 		int inOpen=contain(open,n);
 		int inClose=contain(close,n);
 		if(inOpen==2||inClose==2){
 			struct list* p;
 			if(getList(open, n)!=NULL)
 				p=getList(open,n);
 			if(getList(close, n)!=NULL)
 				p=getList(close,n);
 			freeNode(&p->prev);
 			p->prev=newNode(node->left, node->middle,node->right,node->depth,node->leftSize, node->middleSize, node->rightSize);	
 		}
		if((open==NULL)||(inOpen==0&&inClose==0)){
			struct list* add=newList(n,node,left[0],2);
			append(&open,add);
			deleteList(&add);
		}
		freeNode(&n);
	} 
	
	if(node->leftSize!=0 && (node->rightSize==0||right[0]>left[0])){
		move(&left,&right,node->leftSize, node->rightSize);
		struct node* n=newNode(left,middle,right,node->depth+1,node->leftSize-1,node->middleSize, node->rightSize+1);
		free(left);
		free(right);
		if(node->leftSize!=0){
			left=(int*)calloc(node->leftSize,sizeof(int));
			memcpy(left, node->left, node->leftSize*sizeof(int));
		}else left=NULL;
		if(node->rightSize!=0){
			right=(int*)calloc(node->rightSize,sizeof(int));
			memcpy(right, node->right, node->rightSize*sizeof(int));
		}else right=NULL;
		
		int inOpen=contain(open,n);
 		int inClose=contain(close,n);
 		if(inOpen==2||inClose==2){
 			struct list* p;
 			if(getList(open, n)!=NULL)
 				p=getList(open,n);
 			if(getList(close, n)!=NULL)
 				p=getList(close,n);
 			freeNode(&p->prev);
 			p->prev=newNode(node->left, node->middle,node->right,node->depth,node->leftSize, node->middleSize, node->rightSize);
 			
 		}
		if((open==NULL)||(inOpen==0&&inClose==0)){
			struct list* add=newList(n,node,left[0],3);
			append(&open,add);
			deleteList(&add);
		}
		freeNode(&n);
	}
	
	if(node->middleSize!=0 && (node->leftSize==0||left[0]>middle[0])){
		move(&middle,&left,node->middleSize, node->leftSize);
		struct node* n=newNode(left,middle,right,node->depth+1,node->leftSize+1,node->middleSize-1, node->rightSize);
		free(left);
		free(middle);
		if(node->leftSize!=0){
			left=(int*)calloc(node->leftSize,sizeof(int));
			memcpy(left, node->left, node->leftSize*sizeof(int));
		}else left=NULL;
		if(node->middleSize!=0){
			middle=(int*)calloc(node->middleSize,sizeof(int));
			memcpy(middle, node->middle, node->middleSize*sizeof(int));
		}else middle=NULL;
		
		int inOpen=contain(open,n);
 		int inClose=contain(close,n);
 		if(inOpen==2||inClose==2){
 			struct list* p;
 			if(getList(open, n)!=NULL)
 				p=getList(open,n);
 			if(getList(close, n)!=NULL)
 				p=getList(close,n);
 			freeNode(&p->prev);
 			p->prev=newNode(node->left, node->middle,node->right,node->depth,node->leftSize, node->middleSize, node->rightSize);
 			
 		}
		if((open==NULL)||(inOpen==0&&inClose==0)){
			struct list* add=newList(n,node,middle[0],1);
			append(&open,add);
			deleteList(&add);
		}
		freeNode(&n);
	}
	
	if(node->middleSize!=0 && (node->rightSize==0||right[0]>middle[0])){
		move(&middle,&right,node->middleSize, node->rightSize);
		struct node* n=newNode(left,middle,right,node->depth+1,node->leftSize,node->middleSize-1, node->rightSize+1);
		free(right);
		free(middle);
		if(node->rightSize!=0){
			right=(int*)calloc(node->rightSize,sizeof(int));
			memcpy(right, node->right, node->rightSize*sizeof(int));
		}else right=NULL;
		if(node->middleSize!=0){
			middle=(int*)calloc(node->middleSize,sizeof(int));
			memcpy(middle, node->middle, node->middleSize*sizeof(int));
		}else middle=NULL;
		
		int inOpen=contain(open,n);
 		int inClose=contain(close,n);
 		if(inOpen==2||inClose==2){
 			struct list* p;
 			if(getList(open, n)!=NULL)
 				p=getList(open,n);
 			if(getList(close, n)!=NULL)
 				p=getList(close,n);
 			freeNode(&p->prev);
 			p->prev=newNode(node->left, node->middle,node->right,node->depth,node->leftSize, node->middleSize, node->rightSize);
 			
 		}
		if((open==NULL)||(inOpen==0&&inClose==0)){
			struct list* add=newList(n,node,middle[0],3);
			append(&open,add);
			deleteList(&add);
		}
		freeNode(&n);
	}
	
	if(node->rightSize!=0 && (node->middleSize==0||middle[0]>right[0])){
		move(&right,&middle,node->rightSize, node->middleSize);
		struct node* n=newNode(left,middle,right,node->depth+1,node->leftSize,node->middleSize+1, node->rightSize-1);
		free(right);
		free(middle);
		if(node->rightSize!=0){
			right=(int*)calloc(node->rightSize,sizeof(int));
			memcpy(right, node->right, node->rightSize*sizeof(int));
		}else right=NULL;
		if(node->middleSize!=0){
			middle=(int*)calloc(node->middleSize,sizeof(int));
			memcpy(middle, node->middle, node->middleSize*sizeof(int));
		}else middle=NULL;
		
		int inOpen=contain(open,n);
 		int inClose=contain(close,n);
 		if(inOpen==2||inClose==2){
 			struct list* p;
 			if(getList(open, n)!=NULL)
 				p=getList(open,n);
 			if(getList(close, n)!=NULL)
 				p=getList(close,n);
 			freeNode(&p->prev);
 			p->prev=newNode(node->left, node->middle,node->right,node->depth,node->leftSize, node->middleSize, node->rightSize);
 			
 		}
		if((open==NULL)||(inOpen==0&&inClose==0)){
			struct list* add=newList(n,node,right[0],2);
			append(&open,add);
			deleteList(&add);
		}		
		freeNode(&n);

	} 

	if(node->rightSize!=0 && (node->leftSize==0||left[0]>right[0])){
		move(&right,&left,node->rightSize, node->leftSize);
		struct node* n=newNode(left,middle,right,node->depth+1,node->leftSize+1,node->middleSize, node->rightSize-1);
		free(left);
		free(right);
		if(node->leftSize!=0){
		left=(int*)calloc(node->leftSize,sizeof(int));
		memcpy(left, node->left, node->leftSize*sizeof(int));
		}else left=NULL;
		if(node->rightSize!=0){
		right=(int*)calloc(node->rightSize,sizeof(int));
		memcpy(right, node->right, node->rightSize*sizeof(int));
		}else right=NULL;
		
		int inOpen=contain(open,n);
 		int inClose=contain(close,n);
 		if(inOpen==2||inClose==2){
 			struct list* p;
 			if(getList(open, n)!=NULL)
 				p=getList(open,n);
 			if(getList(close, n)!=NULL)
 				p=getList(close,n);
 			freeNode(&p->prev);
 			p->prev=newNode(node->left, node->middle,node->right,node->depth,node->leftSize, node->middleSize, node->rightSize);
 			
 		}
		if((open==NULL)||(inOpen==0&&inClose==0)){
			struct list* add=newList(n,node,right[0],1);
			append(&open,add);
			deleteList(&add);
		}
		freeNode(&n);
 	}

 	moveNodes(&open,&close);
 	
 	//free memory
	if(left!=NULL){
		free(left);
		left=NULL;
	}
	if(middle!=NULL){
		free(middle);
		middle=NULL;
	}
	if(right!=NULL){
		free(right);
		right=NULL;
	}
	
}

int main(int argc, char *argv[]){
	printf("The number of disks: ");
	scanf("%d", &N);
	
	struct node* start=ini(N);
	close=newList(start,NULL,0,0);
	
	//expand the searching graph
	struct list* p=close;	
	while(p!=NULL){
		expand(p->node);
		if(contain_goal(close,N)!=NULL)
			break;
		p=p->next;
	}
	deleteList(&open);
	
	//collect the movement to "path" struct and print out the result
	struct list* goal=contain_goal(close,N);
	int move=goal->node->depth+goal->node->h;
	printf("%d ", move);
	
	struct path* path=(struct path*)malloc(sizeof(struct path));
	path->disk=goal->disk;
	path->to=goal->toPole;
	path->next=NULL;
	
	p=goal;
	struct node* pn;
	while(p->prev!=NULL){
		pn=p->prev;
		p=getList(close,pn);
		if(p->disk==0||p->toPole==0) break;
		struct path* pp=(struct path*)malloc(sizeof(struct path));
		pp->disk=p->disk;
		pp->to=p->toPole;
		pp->next=path;
		path=pp;
	}
	
	//print out path
	while(path!=NULL){
		printf("%d %d ",path->disk, path->to);
		path=path->next;
	}
	printf("\n");
	
}


