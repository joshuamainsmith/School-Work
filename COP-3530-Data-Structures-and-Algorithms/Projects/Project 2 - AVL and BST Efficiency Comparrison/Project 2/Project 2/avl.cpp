#include "avl.h"

void AVLprocFile(const char* FileName, DWORD dSize, double timeArr[])
{
	struct Node* root = NULL;

	// *********************** Insertion *********************** 
	FILE* fInsert;
	INT buff[255];
	INT i = 1;

	fopen_s(&fInsert, FileName, "r");

	auto start = chrono::high_resolution_clock::now();

	while (i <= dSize)
	{
		fscanf_s(fInsert, "%d", &buff);
		//printf("%d\n", buff[0]);
		root = insert(root, buff[0]);
		i++;
	}

	auto end = chrono::high_resolution_clock::now();

	double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	time_taken *= 1e-3;

	//printf("Insert: %.2f\n", time_taken);
	
	i = 1;
	while (timeArr[i] != -1)
	{
		i++;
	}

	timeArr[i] = time_taken;

	fclose(fInsert);


	// *********************** Traversal *********************** 
	start = chrono::high_resolution_clock::now();

	preOrder(root);

	end = chrono::high_resolution_clock::now();

	time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	time_taken *= 1e-3;

	//printf("Traversal: %.2f\n", time_taken);

	i = 1;
	while (timeArr[i] != -1)
	{
		i++;
	}

	timeArr[i] = time_taken;

	// *********************** Deletion *********************** 
	FILE* fDelete;
	i = 1;

	fopen_s(&fDelete, FileName, "r");

	start = chrono::high_resolution_clock::now();

	while (i <= dSize)
	{
		fscanf_s(fDelete, "%d", &buff);
		//printf("%d\n", buff[0]);
		root = deleteNode(root, buff[0]);
		i++;
	}

	end = chrono::high_resolution_clock::now();

	time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	time_taken *= 1e-3;

	//printf("Delete: %.2f\n\n", time_taken);

	i = 1;
	while (timeArr[i] != -1)
	{
		i++;
	}

	timeArr[i] = time_taken;

	fclose(fDelete);
}

INT avlStart()
{
	double timeArr[35];
	int i = 0;
	for (i = 1; i < 35; i++)
	{
		timeArr[i] = -1;
	}

	//		Small (as/ds/ra)
	AVLprocFile("Files//sm_as.txt", 100, timeArr);

	AVLprocFile("Files//sm_ds.txt", 100, timeArr);

	AVLprocFile("Files//sm_ra.txt", 100, timeArr);

	//		Medium (as/ds/ra)
	AVLprocFile("Files//me_as.txt", 1000, timeArr);

	AVLprocFile("Files//me_ds.txt", 1000, timeArr);

	AVLprocFile("Files//me_ra.txt", 1000, timeArr);
	
	//		Large (as/ds/ra)
	AVLprocFile("Files//la_as.txt", 10000, timeArr);

	AVLprocFile("Files//la_ds.txt", 10000, timeArr);

	AVLprocFile("Files//la_ra.txt", 10000, timeArr);

	printf("************************* AVL *************************\n");

	i = 1;
	// Insert
	printf("Insertion\tAscending\tDescending\tRandon\n");
	printf("Small\t\t");
	while (timeArr[i] != -1)
	{
		if (i == 10)
			printf("\nMedium\t\t");
		if (i == 19)
			printf("\nLarge\t\t");
		printf("%.0f\t\t", timeArr[i]);

		i+=3;
	}

	i = 2;
	// Traversal
	printf("\n\nTraverse\tAscending\tDescending\tRandon\n");
	printf("Small\t\t");
	while (timeArr[i] != -1)
	{
		if (i == 11)
			printf("\nMedium\t\t");
		if (i == 20)
			printf("\nLarge\t\t");
		printf("%.0f\t\t", timeArr[i]);

		i+=3;
	}

	i = 3;
	// Delete
	printf("\n\nDeletion\tAscending\tDescending\tRandon\n");
	printf("Small\t\t");
	while (timeArr[i] != -1)
	{
		if (i == 12)
			printf("\nMedium\t\t");
		if (i == 21)
			printf("\nLarge\t\t");
		printf("%.0f\t\t", timeArr[i]);

		i+=3;
	}

	printf("\n\n");


	return 0;
}

INT height(struct Node* N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

INT maxHeight(INT a, INT b)
{
	return (a > b) ? a : b;
}

struct Node* newNodeAVL(INT key)
{
	struct Node* node = (struct Node*) malloc(sizeof(struct Node));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; 
	return(node);
}

struct Node* rightRotate(struct Node* y)
{
	struct Node* x = y->left;
	struct Node* T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = maxHeight(height(y->left), height(y->right)) + 1;
	x->height = maxHeight(height(x->left), height(x->right)) + 1;

	return x;
}

struct Node* leftRotate(struct Node* x)
{
	struct Node* y = x->right;
	struct Node* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = maxHeight(height(x->left), height(x->right)) + 1;
	y->height = maxHeight(height(y->left), height(y->right)) + 1;

	return y;
}

INT getBalance(struct Node* N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

struct Node* insert(struct Node* node, INT key)
{
	if (node == NULL)
		return(newNodeAVL(key));

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else
		return node;

	node->height = 1 + maxHeight(height(node->left), height(node->right));

	INT balance = getBalance(node);

	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

void preOrder(struct Node* root)
{
	if (root != NULL)
	{
		//printf("%d ", root->key);
		preOrder(root->left);
		preOrder(root->right);
	}
}

struct Node* lowestNode(struct Node* node)
{
	struct Node* current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}

struct Node* deleteNode(struct Node* root, INT key)
{

	if (root == NULL)
		return root;

	if (key < root->key)
		root->left = deleteNode(root->left, key);

	else if (key > root->key)
		root->right = deleteNode(root->right, key);

	else
	{
		if ((root->left == NULL) || (root->right == NULL))
		{
			struct Node* temp = root->left ? root->left :
				root->right;

			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else 
				*root = *temp;
			free(temp);
		}
		else
		{
			struct Node* temp = lowestNode(root->right);

			root->key = temp->key;

			root->right = deleteNode(root->right, temp->key);
		}
	}

	if (root == NULL)
		return root;

	root->height = 1 + max(height(root->left), height(root->right));

	INT balance = getBalance(root);

	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}