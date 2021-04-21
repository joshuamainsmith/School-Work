#pragma once
#include <Windows.h>
#include<stdio.h> 
#include<stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

// An AVL tree node 
struct Node
{
	INT key;
	struct Node* left;
	struct Node* right;
	INT height;
};

INT avlStart();
INT maxHeight(INT a, INT b);
INT height(struct Node* N);
struct Node* newNodeAVL(INT key);
struct Node* rightRotate(struct Node* y);
struct Node* leftRotate(struct Node* x);
INT getBalance(struct Node* N);
struct Node* insert(struct Node* node, INT key);
void preOrder(struct Node* root);
struct Node* lowestNode(struct Node* node);
struct Node* deleteNode(struct Node* root, INT key);
void AVLprocFile(const char* FileName, DWORD dSize, double timeArr[]);