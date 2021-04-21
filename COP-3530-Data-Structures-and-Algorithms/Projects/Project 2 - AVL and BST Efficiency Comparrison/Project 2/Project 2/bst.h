#pragma once
#include <Windows.h>
#include<stdio.h> 
#include<stdlib.h> 
#include <time.h>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

struct node
{
	INT key;
	struct node* left, * right;
};

INT bstStart();
struct node* search(struct node* root, INT key);
struct node* newNodeBST(INT item);
void preOrder(struct node* root);
struct node* insert(struct node* node, INT key);
struct node* lowestNode(struct node* node);
struct node* deleteNode(struct node* root, INT key);
void BSTprocFile(const char* FileName, DWORD dSize, double timeArr[]);
void rearrangeBTS(node* root, vector<node*>& nodes);
node* rotateAboutMid(struct node* root, vector<node*>& nodes, INT start, INT end);
node* balanceTree(node* root);