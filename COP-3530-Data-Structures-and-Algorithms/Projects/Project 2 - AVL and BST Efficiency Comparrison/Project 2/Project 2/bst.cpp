#include "bst.h"

void BSTprocFile(const char* FileName, DWORD dSize, double timeArr[])
{
	struct node* root = NULL;	

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
		if (i % 4000 == 0)
			root = balanceTree(root);
		i++;
	}
	root = balanceTree(root);

	auto end = chrono::high_resolution_clock::now();

	double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	time_taken *= 1e-3;

	//printf("BST Insert Time: %.2f\n", time_taken);

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

	time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	time_taken *= 1e-3;

	//printf("BST Traversal Time: %.2f\n", time_taken);

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

	//printf("BST Delete Time: %.2f\n\n", time_taken);

	i = 1;
	while (timeArr[i] != -1)
	{
		i++;
	}

	timeArr[i] = time_taken;

	fclose(fDelete);
}

INT bstStart()
{
	double timeArr[35];
	int i = 0;
	for (i = 1; i < 35; i++)
	{
		timeArr[i] = -1;
	}

	//		Small	
	BSTprocFile("Files//sm_as.txt", 100, timeArr);
	
	BSTprocFile("Files//sm_ds.txt", 100, timeArr);

	BSTprocFile("Files//sm_ra.txt", 100, timeArr);

	//		Medium
	BSTprocFile("Files//me_as.txt", 1000, timeArr);

	BSTprocFile("Files//me_ds.txt", 1000, timeArr);

	BSTprocFile("Files//me_ra.txt", 1000, timeArr);

	//		Large
	BSTprocFile("Files//la_as.txt", 10000, timeArr);

	BSTprocFile("Files//la_ds.txt", 10000, timeArr);

	BSTprocFile("Files//la_ra.txt", 10000, timeArr);

	printf("\n************************* BST *************************\n");

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
		printf("%.0f\t", timeArr[i]);

		if (i != 8)
			printf("\t");

		i += 3;
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

		i += 3;
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

		i += 3;
	}

	return 0;
}

struct node* search(struct node* root, INT key)
{
	if (root == NULL || root->key == key)
		return root;

	if (root->key < key)
		return search(root->right, key);

	return search(root->left, key);
}

struct node* newNodeBST(INT item)
{
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

void preOrder(struct node* root)
{
	if (root == NULL)
		return;

	//printf("%d ", root->key);
	preOrder(root->left);
	preOrder(root->right);
}

struct node* insert(struct node* node, INT key)
{
	if (node == NULL)
		return newNodeBST(key);

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);

	return node;
}

struct node* lowestNode(struct node* node)
{
	struct node* current = node;

	while (current && current->left != NULL)
		current = current->left;

	return current;
}

struct node* deleteNode(struct node* root, INT key)
{
	if (root == NULL) return root;

	if (key < root->key)
		root->left = deleteNode(root->left, key);

	else if (key > root->key)
		root->right = deleteNode(root->right, key);

	else
	{
		if (root->left == NULL)
		{
			struct node* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			struct node* temp = root->left;
			free(root);
			return temp;
		}

		struct node* temp = lowestNode(root->right);

		root->key = temp->key;

		root->right = deleteNode(root->right, temp->key);
	}
	return root;
}

void rearrangeBTS(struct node* root, vector<node*>& nodes)
{
	if (root == NULL)
		return;

	rearrangeBTS(root->left, nodes);
	nodes.push_back(root);
	rearrangeBTS(root->right, nodes);
}

node* rotateAboutMid(struct node* root, vector<node*>& nodes, INT start, INT end)
{
	if (start > end)
		return NULL;

	INT mid = (start + end) / 2;
	root = nodes[mid];

	root->left = rotateAboutMid(root, nodes, start, mid - 1);
	root->right = rotateAboutMid(root, nodes, mid + 1, end);

	return root;
}


node* balanceTree(struct node* root)
{
	vector<node*> nodes;
	rearrangeBTS(root, nodes);

	int n = nodes.size();
	return rotateAboutMid(root, nodes, 0, n - 1);
}