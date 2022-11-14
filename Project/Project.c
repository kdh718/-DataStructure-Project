#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

typedef struct node* node;
typedef struct node {
	struct node* left;
	struct node* right;
	struct node* parent;
	int num;
} NODE;
typedef struct queue* queuePointer;
typedef struct queue {
	int data;
	queuePointer link;
} queue;
typedef struct graph* graphPointer;
typedef struct graph {
	int data;
	graphPointer link;
} graph;
int indexnumber(NODE* root, int num);
graph* Create(NODE* tree);
void inorder(node tree);
void addq(queuePointer* front, queuePointer* rear, int i);
int deleteq(queuePointer* front);
NODE* CreateBTree(NODE* parent, int max_num);
NODE* SearchBFS(NODE* root, int num);
int push(int data);
void main() {
	NODE* tree = (node*)malloc(sizeof(node));
	int MAX;
	char num1;
	printf("(입력1) ");
	scanf("%d", &MAX);
	printf("%d ", MAX);
	getchar();
	
	tree->num = MAX;
	tree->left = NULL;
	tree->right = NULL;
	CreateBTree(tree, MAX);
	inorder(tree);
	printf("\n(입력2) ");
	scanf("%c", &num1);
	
	SearchBFS(tree, num1);
	
}

NODE* CreateBTree(NODE* tree, int max_num)
{
	int i, j = 0;
	int Depth = ceil(log(max_num) / log(2));
	int number = pow(2, Depth);
	for (i = 1; i < number ; i++)
	{
		(tree + i)->num = i;
		(tree + i)->left = NULL;
		(tree + i)->right = NULL;
		
	}
	i = 0;
	for (j = number; j < number+max_num; j++)
		{
			(tree + j)->num = 65 + i;
			(tree + j)->left = NULL;
			(tree + j)->right = NULL;
			i++;
		}

	for (i = 1; i < number + max_num; i++)
	{
		j = floor(i / 2);

		if (i % 2 == 0 )
			(tree + j)->left = (tree + i);
		
		else
			(tree + j)->right = (tree + i);
		(tree + i)->parent = (tree + j);
	}
	


}


void inorder(node tree)
{
	if (tree!=NULL)
	{
		
		inorder(tree->left);
		if(tree->num!=0)
			if(tree->num>=65)
				printf("%c ", tree->num);
			else
				printf("%d ", tree->num);
		inorder(tree->right);
	}
	
}

NODE* SearchBFS(NODE* root, int num)
{
	graph* G = Create(root);
	graph* w = (graph*)malloc(sizeof(graph));
	int i = 1;
	int y = num;
	int size = root->num;
	int Depth = ceil(log(size) / log(2));
	int x = Depth;
	int number = pow(2, Depth);
	int visited[91] = {0,};
	queuePointer front, rear;
	front = rear = NULL;
	visited[num] = 1;
	i = indexnumber(root, num);
	if (root->num % 2 == 1)
	{
		visited[num] = 0;
		addq(&front, &rear, (G + i)->link->data);
	}
	else
		addq(&front, &rear, num);
	while (front!=NULL) 
	{
		
		num = deleteq(&front);
		i=indexnumber(root, num);

		for (w = (G+i); w!=NULL; w=w->link)
		{
			if (visited[w->data] == 0)
			{
				number = pow(2, x);
				if (x == Depth)
				{
					if (w->data >= number )
					{
						if (w->data >= 65)
							printf("%5c", w->data);
						else
							printf("%5d", w->data);

						x--;
					}
				}
				else
				{
					if (w->data >= number && w->data < 2 * number)
					{
						if (w->data >= 65)
							printf("%5c", w->data);
						else
							printf("%5d", w->data);
						
						x--;
					}
				}		
				addq(&front, &rear, w->data);
				visited[w->data] = 1;
			}
			if (x == 0)
			{
				front = NULL; rear = NULL;
				break;
			}
			
			if (root->num % 2 == 1)
			{
				if (w->data == y)
				{
					if (w->data >= 65)
						printf("%5c", w->data);
					else
						printf("%5d", w->data);
					x--;
				}
			}

		}
	
	}
	
}

void addq(queuePointer* front, queuePointer* rear, int i)
{
	queuePointer temp = (queuePointer)malloc(sizeof(queue));
	temp->data = i;
	temp->link = NULL;
	if (*front)
		(*rear)->link = temp;
	else
		(*front) = temp;
	*rear = temp;
}

int deleteq(queuePointer* front)
{
	queuePointer temp = *front;
	int i;
	i = temp->data;
	*front = temp->link;
	free(temp);
	return i;
}

graph* Create(NODE* tree)
{
	graph* G = (graph*)malloc(sizeof(graph));
	int i = tree->num;
	int j;
	int Depth = ceil(log(i) / log(2));
	int number = pow(2, Depth);
	for(j=1; j<i+number;j++)
	{
		if (j == 1)
		{
			(G + j)->data = (tree + j)->num;
			(G + j)->link = push((tree + j)->left->num);
			(G + j)->link->link = push((tree + j)->right->num);
		}
		else
		{
			
			(G + j)->data = (tree + j)->num;
			(G + j)->link = push((tree + j)->parent->num);
			if ((tree + j)->left != NULL)
				(G + j)->link->link = push((tree + j)->left->num);
			else
				(G + j)->link->link = NULL;
			if ((tree + j)->right != NULL)
				(G + j)->link->link->link = push((tree + j)->right->num);


		}
	}

	return G;
}

int push(int data) {
	graph* ptr;
	ptr = (graph*)malloc(sizeof(graph));
	if (ptr == NULL) {
		printf("메모리 할당에 실패했습니다.\n");
		return -1;
	}
	ptr->data = data;
	ptr->link = NULL;
	return ptr;
}

int indexnumber(NODE* root, int num)
{
	int i = 0;
	while (1)
	{
		if ((root + i)->num == num)
			break;
		i++;
	}
	return i;
}