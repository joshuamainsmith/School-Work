#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <iomanip>
#include <vector>
#include <math.h>

using namespace std;
/*
Adjacency Matrix struct
*/
struct AdjacencyMatrix
{
	AdjacencyMatrix(int d);

	double matVal(int r, int c);
	void setMatVal(int from, int to, double val);   

	int d;
	double* m;
};

/*
Created Graph struct
*/
struct Created_Graph
{
	Created_Graph(int no_lines, int itr);
	void resizeMat(int nVal);

	int nPages;
	int pItr;
	vector<string> url;
	vector<double> pRank;
	AdjacencyMatrix* adjMatrix;
	//void addEdge(vector<int> adj[], int u, int v);
	int indexVal(string url);
	//void union1(int i, int j);
	//void printGraph(vector<int> adj[], int V);
	//int find(int i);
};

int main()
{

	int no_of_lines, pItr;
	std::string from, to;

	std::cin >> no_of_lines;
	std::cin >> pItr;

	//for (int i = 0; i < no_of_lines; i++)
	//{
	//	std::cin >> from;
	//	std::cin >> to;
	//	// Do Something
	//}

	////Create a graph
	Created_Graph PageRank(no_of_lines, pItr);

	return 0;
}

//void Created_Graph::addEdge(vector<int> adj[], int u, int v)
//{
//	adj[u].push_back(v);
//	adj[v].push_back(u);
//}

/*
Constructor adding url's to matrix, evaluating power itr, and printing results
*/
Created_Graph::Created_Graph(int no_lines, int itr)
{
	pItr = itr;
	nPages = no_lines * 2;
	adjMatrix = new AdjacencyMatrix(nPages);
	string tmp;
	int from = -1, to = -1;

	for (int i = 0; i < no_lines; i++)
	{
		tmp = "";
		cin >> tmp;
		from = indexVal(tmp);
		if (!(from > -1))
		{
			from = url.size();
			url.push_back(tmp);
		}

		tmp = "";
		cin >> tmp;
		to = indexVal(tmp);
		if (!(to > -1))
		{
			to = url.size();
			url.push_back(tmp);
		}

		adjMatrix->setMatVal(from, to, 1);
	}

	nPages = url.size();

	double* temp = new double[nPages * nPages];

	for (int r = 0; r < nPages; r++)
	{
		for (int c = 0; c < nPages; c++)
		{
			temp[(r * nPages) + c] = adjMatrix->m[(r * adjMatrix->d) + c];
		}
	}

	delete[] adjMatrix->m;
	adjMatrix->m = temp;
	adjMatrix->d = nPages;

	int o;
	for (int r = 0; r < nPages; r++)
	{
		o = 0;
		for (int c = 0; c < nPages; c++)
		{
			if (adjMatrix->matVal(r, c) != 0)
			{
				o++;
			}
		}
		for (int c = 0; c < nPages; c++)
		{
			if (adjMatrix->matVal(r, c) != 0)
			{
				adjMatrix->setMatVal(r, c, (adjMatrix->matVal(r, c)) / o);
			}
		}
	}

	pRank.resize(nPages, 1.0 / nPages);

	resizeMat(pItr - 1);

	vector<string> output = url;

	printf("\n");

	for (int i = 0; i < nPages; i++)
	{
		output.at(i) = output.at(i) + " " + to_string(floor(pRank.at(i) * 100 + 0.5) / 100).substr(0, 4);
	}

	sort(output.begin(), output.end());

	for (int i = 0; i < nPages; i++)
	{
		cout << output.at(i) << "\n";
	}
}

//
//int Created_Graph::find(int i)
//{
//	while (parent[i] != i)
//		i = parent[i];
//	return i;
//}

//void Created_Graph::union1(int i, int j)
//{
//	int a = find(i);
//	int b = find(j);
//	parent[a] = b;
//}

/*
Return index value of inquired matrix
*/
int Created_Graph::indexVal(string tmp)
{
	for (int i = 0; i < url.size(); i++)
	{
		if (url.at(i).compare(tmp) == 0)
		{
			return i;
		}
	}
	return -1;
}

//void Created_Graph::printGraph(vector<int> adj[], int V)
//{
//	for (int v = 0; v < V; ++v)
//	{
//		cout << "\n Adjacency list of vertex "
//			<< v << "\n head ";
//		for (auto x : adj[v])
//			cout << "-> " << x;
//		printf("\n");
//	}
//}

/*
Return index value of inquired matrix
*/
void Created_Graph::resizeMat(int tItr)
{
	double sum = 0;
	vector<double> tmp;

	for (int i = 0; i < tItr; i++)
	{
		tmp.clear();
		for (int c = 0; c < nPages; c++)
		{
			sum = 0;
			for (int r = 0; r < nPages; r++)
			{
				sum += (adjMatrix->matVal(r, c)) * pRank.at(r);
			}
			tmp.push_back(sum);
		}
		pRank = tmp;
	}
}

AdjacencyMatrix::AdjacencyMatrix(int temp)
{
	d = temp;

	m = new double[d * d];

	for (int i = 0; i < d * d; i++)
	{
		m[i] = 0;
	}
}

double AdjacencyMatrix::matVal(int r, int c)
{
	return m[(r * d) + c];
}

void AdjacencyMatrix::setMatVal(int from, int to, double val)
{
	m[(from * d) + to] = val;
}



