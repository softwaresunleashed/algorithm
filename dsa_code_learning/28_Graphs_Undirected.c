/******************************************************************************
    Graphs_Undirected.c
	===================

	Vertex Representation :: 
	---------------------
	Use integers between 0 and V-1. If needed in application, convert between 
	names and integers with symbol tables.
	
	Degree(v) : means the number of vertex(s) connected immediately to vertex v
	
	Graphs API
	----------
	Graph(int V) 					create an empty graph with V vertices
	Graph(In in) 					create a graph from input stream
	void addEdge(int v, int w) 		add an edge v-w
	Iterable<Integer> adj(int v) 	vertices adjacent to v
	int V() 						number of vertices
	int E() 						number of edges
	
	Print Adjacent Vertices 
	-----------------------
	In in = new In(args[0]);
	Graph G = new Graph(in);
	for (int v = 0; v < G.V(); v++)
		for (int w : G.adj(v))
			StdOut.println(v + "-" + w);
	
	Compute Degree of Vertex
	------------------------
	public static int degree(Graph G, int v)
	{
		int degree = 0;
		for (int w : G.adj(v)) degree++;
		return degree;
	}

	Compute Maximum Degree
	----------------------
	public static int maxDegree(Graph G)
	{
		int max = 0;
		for (int v = 0; v < G.V(); v++)
			if (degree(G, v) > max)
				max = degree(G, v);
		return max;
	}

	Compute Average Degree
	----------------------
	public static double averageDegree(Graph G)
	{
		return 2.0 * G.E() / G.V();
	}

	Count Self-loops
	----------------
	public static int numberOfSelfLoops(Graph G)
	{
		int count = 0;
		for (int v = 0; v < G.V(); v++)
			for (int w : G.adj(v))
				if (v == w) 
					count++;
		return count/2; // each edge counted twice
	}

	Adjacency-"Matrix" of graph representation (Not Widely Used Method)
	------------------------------------------
	Maintain a 2D V by V boolean array;
	for each edge v-w in graph : adj[v][w] == adj[w][v] => true
	** Two entries for each edge
	
		adj		|	0	|	1	|	2	|	3
		---------------------------------------
			0 	|	0	|	0	|	0	|	0
			1	|	0	|	0	|	1	|	0
			2	|	0	|	1	|	0	|	0
			3	|	0	|	0	|	0	|	0

		
	Adjacency-"List" of graph representation	
	----------------------------------------
	Maintain vertex-indexed array of lists.
	
	adj[]
	=====
	0 []--------->[ [6] -> [2] -> [1] -> [5] ]
	1 []--------->[ [0] ]
	2 []--------->[ [0] ]
	3 []--------->[ [5] -> [6] -> [3] ]
	
	public class Graph
	{
		private final int V;
		private Bag<Integer>[] adj;

		public Graph(int V)
		{
			this.V = V;
			adj = (Bag<Integer>[]) new Bag[V];
			for (int v = 0; v < V; v++)
			adj[v] = new Bag<Integer>();
		}

		public void addEdge(int v, int w)
		{
			adj[v].add(w);
			adj[w].add(v);
		}
		 
		public Iterable<Integer> adj(int v)
		{ 
			return adj[v];
		}
	}


	In Practice:
	------------
	* Real world graphs tend to be sparse. 
	* Sparse means :-
		* Less Vertexes, and 
		* More of Edges (More Vertex Degree) ie. implemented by Linked List of connected Vertices
	
	
	
	
	
	
*******************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define TRUE 1
#define FALSE 0


typedef struct linked_list
{
	int vertex_num;
	struct linked_list *next;
} linked_list_t;

typedef struct vertex_bag
{
	int bag_size;
	linked_list_t *bag_head;
} vertex_bag_t;

typedef struct graph
{
	vertex_bag_t *v;	// Array of vertices
	int v_size;	
} graph_t;

graph_t * init_graph(int num_of_vertices)
{
	graph_t * graph = (graph_t *)malloc(sizeof(graph_t));
	int i = 0;
	
	if(graph)
	{
	    graph->v_size = num_of_vertices;
		graph->v = (vertex_bag_t *)malloc(num_of_vertices * sizeof(vertex_bag_t));
		if(graph->v)
		{
		
			for(i = 0; i < num_of_vertices; i++)
			{
			    graph->v[i].bag_size = 0;
			    graph->v[i].bag_head = NULL;
			}
			return graph;
		}
	}
	return NULL;	
}

linked_list_t * create_new_node(int w)
{
    linked_list_t * temp_node = malloc(sizeof(linked_list_t));
    if(temp_node)
    {
        temp_node->vertex_num = w;
        temp_node->next = NULL;
    }

    return temp_node;
}

void add_to_bag(vertex_bag_t * bag, int w)
{
	if(bag->bag_head == NULL)
	{
		bag->bag_head = create_new_node(w);
		bag->bag_size = 1;
	}
	else
	{
		// Loop till end of bag
		linked_list_t * temp_node = bag->bag_head;
		while(temp_node->next != NULL)
			temp_node = temp_node->next;
		
		temp_node->next = create_new_node(w);
		
		// Increase the size of bag by one
		bag->bag_size++;
	}
}

void addEdge(graph_t * graph_instance, int v, int w)
{

	if(graph_instance)
	{
		//Add edge w to vertice v :- adj[v].add(w);
		add_to_bag(&graph_instance->v[v], w);
		
		//Add edge v to vertice w :- adj[w].add(v);	
		add_to_bag(&graph_instance->v[w], v);
	}
}

linked_list_t * adjacent(graph_t * graph_instance, int v)
{ 
	return graph_instance->v[v].bag_head;
}

/* Print Adjacent Vertices */
void print_adjacent(graph_t * graph_instance, int v)
{ 
	/* Get Iterator of adjacent vertices to vertice-v*/
    linked_list_t * temp = adjacent(graph_instance, v);
    printf("\nAdjacent Vertices connnected to vertex %d : ", v);
    while(temp != NULL)
    {
        printf("%d-%d ", v, temp->vertex_num);
        temp =  temp->next;
    }
}

/* Returns degree of a specific vertex */
int degree(graph_t * graph_instance, int v)
{
    vertex_bag_t * vertex_bag = &graph_instance->v[v];
	if(vertex_bag)
		return graph_instance->v[v].bag_size;
	else 
		return 0;
}

/* Returns the maximum degree of the graph */
int max_degree(graph_t * graph_instance)
{
	int max_degree = 0;
	int bag_size = 0;
	int total_graph_vertices = 0;
	
	if(graph_instance)
	{
		total_graph_vertices = graph_instance->v_size;
		for(int i = 0; i < total_graph_vertices; i++)
		{
			bag_size = degree(graph_instance, i);
			if(bag_size > max_degree)
				max_degree = bag_size;
		}
	}
	return max_degree;	
}

int number_of_self_loops(graph_t * graph_instance)
{
	int self_loops_count = 0;
	linked_list_t * adjacent_nodes = NULL;
	
	if(graph_instance)
	{

		for(int i = 0; i < graph_instance->v_size; i++)
		{
			adjacent_nodes = adjacent(graph_instance, i);
			if(adjacent_nodes)
			{
				while(adjacent_nodes->next != NULL)
				{
					if(adjacent_nodes->vertex_num == i)
						self_loops_count++;

					adjacent_nodes = adjacent_nodes->next;
				}
			}
		}
	}
			
	return self_loops_count/2; // each edge counted twice
}

/*

Enter the number of Vertices : 7                                                                                                                                 

Enter the number of Edge pairs : 8                                                                                                                               

Edge Pair [1] : 0 6                                                                                                                                              

Edge Pair [2] : 0 2                                                                                                                                              

Edge Pair [3] : 0 1                                                                                                                                              

Edge Pair [4] : 0 5                                                                                                                                              

Edge Pair [5] : 3 5                                                                                                                                              

Edge Pair [6] : 3 4                                                                                                                                              

Edge Pair [7] : 5 4

Edge Pair [8] : 0 0

Enter the Vertex for which adjacent Vertex are required : 2                                                                                                      

Adjacent Vertices connnected to vertex 2 : 2-0                                                                                                                   
=======================================================                                                                                                          
Max Degree of Graph : 4                                                                                                                                          
=======================================================

*/

int main()
{
	int i = 0, vertices = 0, edges = 0, adj_vertex = 0;
	int v1 = 0, v2 = 0;
	graph_t * graph_instance = NULL;
	
	// Get number of vertices and initialize the graph
	printf("\nEnter the number of Vertices : ");
	scanf("%d", &vertices);
	graph_instance = init_graph(vertices);
	
	// Add graph edges
	printf("\nEnter the number of Edge pairs : ");
	scanf("%d", &edges);
	if(graph_instance)
	{
		for(i = 0; i < edges; i++)
		{
			printf("\nEdge Pair [%d] : ", i+1);
			scanf("%d %d", &v1, &v2);
			addEdge(graph_instance, v1, v2);
		}
	}
	
	// Print adjacent list of vertex
	printf("\nEnter the Vertex for which adjacent Vertex are required : ");
	scanf("%d", &adj_vertex);
    print_adjacent(graph_instance, adj_vertex);
    
    // Print max degree of graph
    printf("\n=======================================================");
    printf("\nMax Degree of Graph : %d", max_degree(graph_instance) );
    printf("\n=======================================================");

    // Count number of self loops in graph
    printf("\n=======================================================");
    printf("\nSelf Loops in Graph : %d", number_of_self_loops(graph_instance) );
    printf("\n=======================================================");

	
	getch();
    return 0;
}
