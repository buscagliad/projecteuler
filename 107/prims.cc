#include <stdio.h>
#include <limits.h>
#include <iostream>
#include <cstring>

using namespace std;
 
// Number of vertices in the graph
#define V 40
 
// A utility function to find the vertex with minimum key value, from
// the set of vertices not yet included in MST
int minKey(int key[], bool mstSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
    if (mstSet[v] == false && key[v] < min)
    min = key[v], min_index = v;
 
    return min_index;
}
 
// A utility function to print the constructed MST stored in parent[]
void printMST(int parent[], int n, int graph[V][V], int &w)
{
    cout<<"Edge   Weight\n";
    w = 0;
    for (int i = 1; i < V; i++)
    {
		w += graph[i][parent[i]];
        printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
	}
	printf("Total weight: %d\n", w);
}
 
// Function to construct and print MST for a graph represented using adjacency
// matrix representation
void primMST(int graph[V][V], int &finw)
{
    int parent[V]; // Array to store constructed MST
    int key[V]; // Key values used to pick minimum weight edge in cut
    bool mstSet[V]; // To represent set of vertices not yet included in MST
 
    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
 
    // Always include first 1st vertex in MST.
    key[0] = 0; // Make key 0 so that this vertex is picked as first vertex
    parent[0] = -1; // First node is always root of MST
 
    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick thd minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, mstSet);
 
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
 
        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (int v = 0; v < V; v++)
 
            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
 
    // print the constructed MST
    printMST(parent, V, graph, finw);
}

int	rdfile(const char *fname, int edges[V][V], int &weight)
{
	char   inl[1000];
	char   *ip;
	char   *tok;
	FILE   *f = fopen(fname, "r");
	int	   x = 0;
	int    y = 0;
	weight = 0;
	while (1)
	{
		fgets(inl, 1000, f);
		//printf("y:%d  s: %s\n", y, inl);
		if (feof(f)) break;
		tok = strtok_r(inl, ",", &ip);
		x=0;
		while (tok)
		{
			if (*tok != '-')
			{
				edges[x][y] = atoi(tok);
				weight += edges[x][y];
				//printf("Adding edge: (%d,%d,%d) \n", x, y, atoi(tok));
			}
			else
			{
				edges[x][y] = 0;
			}
			tok = strtok_r(NULL, ",", &ip);
			x++;
		}
		y++;
	}
	weight /= 2;
	return y;
}


// driver program to test above function
int main()
{
    /* Let us create the following graph
     2    3
     (0)--(1)--(2)
     |   / \   |
     6| 8/   \5 |7
     | /     \ |
     (3)-------(4)
     9          */
    int graph[V][V];
    int origw;
    int finalw;
    
    rdfile("p107_network.txt", graph, origw);
    // Print the solution
    primMST(graph, finalw);
    
    printf("Original graph weight: %d\n", origw);
    printf("Final optimized weight: %d\n", finalw);
    printf("Savings: %d\n", origw - finalw);
 
    return 0;
}
