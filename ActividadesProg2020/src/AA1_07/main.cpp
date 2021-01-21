#include <iostream>
#include <list>
#include <iterator>

void printAdjency(std::list<int> adjList[], int u)
{
	for (int i = 1; i < u; i++)
	{
		std::cout << i << "------>";
		std::list<int>::iterator it;
		for (it = adjList[i].begin(); it != adjList[i].end(); it++)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}
}

void addEdge(std::list<int> adjList[], int u, int v)
{
	adjList[u].push_back(v);
	adjList[v].push_back(u);
}

int main()
{
	//Vertices
	//Poder ver la lista de adjacencia de cada uno
	std::list<int> adjList[4];
	addEdge(adjList, 1, 2);
	addEdge(adjList, 3, 2);
	addEdge(adjList, 1, 3);
	printAdjency(adjList, 4);
	return 0;
}