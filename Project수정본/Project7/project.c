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
int intlog2(int i);
int powint(int i, int j);
int floorint(float i);
int indexnumber(NODE* root, int num);
NODE* ChangeRightChild(NODE* tree, int max_num);
NODE* RecallRightChild(NODE* tree, int max_num);
graph* Create(NODE* tree);
void addq(queuePointer* front, queuePointer* rear, int i);
int deleteq(queuePointer* front);
NODE* CreateBTree(NODE* parent, int max_num);
NODE* SearchBFS(NODE* root, int num);
graphPointer push(int data);



int main() {
	
	int MAX;
	char num1;
	printf("(number of node) ");
	scanf("%d", &MAX);
	if (MAX <= 0)
	{
		printf("Tree isn't bulit.");
		exit(0);
	}
	NODE* tree = (node)malloc(sizeof(long long)* 1024*1024);
	
	tree->num = MAX;
	tree->left = NULL;
	tree->right = NULL;
	CreateBTree(tree, MAX);
	if (MAX % 2 == 1)
	{
		ChangeRightChild(tree, MAX);
		tree->num = MAX+1;
	}	
	getchar();
	
	printf("(node to find) ");
	scanf("%c", &num1);
	if (num1 > MAX + 65)
	{
		printf("The leaf node is not in Tree");
		return 0;
	}
	SearchBFS(tree, num1);
	if (MAX % 2 == 1)
		RecallRightChild(tree, MAX);
	printf("\n");
	return 0;
}

NODE* CreateBTree(NODE* tree, int max_num)
{
	int i, j = 0;
	int Depth = intlog2(max_num);
	int number = powint(2, Depth);
	for (i = 1; i < number; i++)
		{
			(tree + i)->num = i;
			(tree + i)->left = NULL;
			(tree + i)->right = NULL;

		}
		i = 0;
	for (j = number; j < number + max_num; j++)
		{
			(tree + j)->num = 65 + i;
			(tree + j)->left = NULL;
			(tree + j)->right = NULL;
			i++;
		}
	for (i = 1; i < number + max_num; i++)
		{
			j = floorint(i / 2);

			if (i % 2 == 0)
				(tree + j)->left = (tree + i);

			else
				(tree + j)->right = (tree + i);
			(tree + i)->parent = (tree + j);
		}
	}


NODE* SearchBFS(NODE* root, int num)
{
	if (root->num % 2 == 0 )
		if(num-(root->num)==63 && num!=65)
			num += 1;
	graph* G = Create(root);
	graph* w = (graph*)malloc(sizeof(long long) * 1024 * 1024);
	int i = 1;
	int y = indexnumber(root, num);
	int size = root->num;
	int Depth = intlog2(size);
	int x = Depth;
	int number = powint(2, Depth);
	int visited[91] = { 0, };
	queuePointer front, rear;
	front = rear = NULL;
	visited[num] = 1;
	addq(&front, &rear, num);
	while (front != NULL)
	{

		num = deleteq(&front);
		i = indexnumber(root, num);
	
		for (w = (G + i); w != NULL; w = w->link)
		{
			if (visited[w->data] == 0)
			{
				number = powint(2, x);
				if (x == Depth)
				{
					if (w->data >= number)
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
					if (w->data >= number && w->data < 2 * number && (w->data)*2 != y)
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
		}

	}
	
}

void addq(queuePointer* front, queuePointer* rear, int i)
{
	queuePointer temp = (queuePointer)malloc(sizeof(long long) * 1024 * 1024);
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

	graph* G = (graph*)malloc(sizeof(long long) * 1024 * 1024);
	int i = tree->num;
	int j;
	int Depth = intlog2(i);
	int number = powint(2, Depth);
	int nodenum = i + number;
	
	
	for (j = 1; j < i + number; j++)
	{
		if (j == 1)
		{
			(G + j)->data = (tree + j)->num;
			(G + j)->link = push((tree + j)->left->num);
			(G + j)->link->link = push((tree + j)->right->num);
		}
		else
		{
			if ((tree + j) == NULL)
				continue;
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

graphPointer push(int data) {
	graph* ptr = (graph*)malloc(sizeof(long long) * 1024 * 1024);
	if (ptr == NULL) {
		printf("Fail\n");
		exit(1);
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
NODE* ChangeRightChild(NODE* tree, int max_num)
{
	int Depth =intlog2(max_num);
	int number = powint(2, Depth);
	(tree + number + max_num)->num = max_num + 64;
	(tree + number + max_num)->left = NULL;
	(tree + number + max_num)->right = NULL;
	((tree + number + max_num))->parent = (tree + number + max_num - 1)->parent;
	(tree + number + max_num - 1)->parent->right = (tree + number + max_num);
	(tree + number + max_num - 1)->num+=1;
	
}
NODE* RecallRightChild(NODE* tree, int max_num)
{
	int Depth = intlog2(max_num);
	int number = powint(2, Depth);
	(tree + number + max_num - 1)->num-=1;
	(tree + number + max_num - 1)->parent->right=NULL;
}
int intlog2(int i)
{
	int k = 0, j = 1;
	while (1)
	{
		if (i % 2 != 0)
			k = 1;
		i /= 2;
		if (i == 1)
			break;
		j++;
	}
	if (k == 1)
		j++;
	return j;
}
int powint(int i, int j)
{
	int l = i;
	for (int k = 1; k < j; k++)
		i *= l;
	if (j == 0)
		i = 1;
	return i;
}
int floorint(float i)
{
	int j = i;
	return j;
}
