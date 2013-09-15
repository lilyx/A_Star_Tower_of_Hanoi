//information about current state
struct node{
	int* left;
	int leftSize;
	int* middle;
	int middleSize;
	int* right;
	int rightSize;
    int depth;
	int h; 			//the heuristic value for this node
};

//list all the state, with the former state, and the step take(dist->toPole) needed from former to current state
struct list{
    struct node* prev;
	struct node* node;
    int disk;
    int toPole;
	struct list* next;
};

//list final steps
struct path{
	int disk;
	int to;
	struct path* next;
};

struct node* newNode(int* left, int* middle, int* right,int depth,int leftSize,int middleSize, int rightSize);
struct node* ini(int n);
struct list* newList(struct node* start, struct node* prev, int disk, int to);
struct list* contain_goal(struct list* list,int n);
int contain(struct list* list, struct node* node);
struct list* getList(struct list* list, struct node* node);
int compareNode(struct node* n1, struct node* n2);
void deleteList(struct list** list);
void append(struct list** list, struct list* ll);
void moveNodes(struct list** from, struct list** to);
void removeFromList(struct list** list, struct node* node);
void move(int** array1, int** array2,int size1,int size2);
void freeNode(struct node** node);
int node_h(struct node* node);



