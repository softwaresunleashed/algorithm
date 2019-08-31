/******************************************************************************
    29_Graphs_Undirected_DFS.c
	========================

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
	
	
	DFS (Depth First Search)
	------------------------
	Goal : Systematically search through a graph, 
			all the vertices connected to src_vertex (and a corresponding path)
	Idea : Mimic maze exploration
	
	DFS(to visit vertex v) : algo
	Mark v as visited
	Recursively visit all unmarked vertices 'w' adjacent to 'v'
	
	Data Structures Used (for DFS) :
	* boolean[] marked - size equal to number of vertices
	* int[] edgeTo - to keep tree of paths
	edgeTo[w] == v means that edge v-w taken to visit w for first time.
	
	private void dfs(Graph G, int v)
	{
		marked[v] = true;
		for (int w : G.adj(v))
			if (!marked[w])
			{
				dfs(G, w);
				edgeTo[w] = v;
			}
	}
	
	Application of DFS -
	------------------
	1) Find all vertices connected to a given source vertex
	2) Find a path between two vertices
	
	DFS Application : 
	Proposition  : After DFS, can find vertices connected to s in constant time
					and can find a path to s (if one exists) in time 
					proportional to its length.

	// Is there a path between src_vertex & dst_vertex
	boolean has_path(int src_vertex, int dst_vertex);	
		
	// path from src_vertex to dst_vertex, NULL if no such path
	Iterator path_to(int src_vertex, int dst_vertex);
	
	Paths paths = new Paths(G, s);
	for (int v = 0; v < G.V(); v++)
		if (paths.hasPathTo(v))
			StdOut.println(v);
	
	public boolean hasPathTo(int v)
	{ 
		return marked[v]; 
	}
	
	public Iterable<Integer> pathTo(int v)
	{
		if (!hasPathTo(v)) 
			return null;
		
		Stack<Integer> path = new Stack<Integer>();
		
		for (int x = v; x != s; x = edgeTo[x])
			path.push(x);
		
		path.push(s);
		return path;
	}
	
	
*******************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

#define DEBUG_ENABLE    0	/* Enable to print debug messages */

typedef struct dfs_ds
{
	bool * marked;
	int  * edge_to;
	int num_of_vertices;
}dfs_ds_t;

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


/* Depth First Search DS Instance */
dfs_ds_t * dfs_ds = NULL;

void dfs(graph_t * graph_instance, int src_vertex)
{
	int num_of_ver = 0;
	linked_list_t * adjacent_vertex_iterator = NULL;
	
	/* Initialize DFS data structure */
	if(dfs_ds == NULL)
	{
		int i = 0;
		dfs_ds = (dfs_ds_t *)malloc(sizeof(dfs_ds_t));

		num_of_ver = dfs_ds->num_of_vertices = graph_instance->v_size;
		dfs_ds->marked = (bool *)malloc(num_of_ver * sizeof(bool));
		dfs_ds->edge_to = (int *)malloc(num_of_ver * sizeof(int));
		for(i = 0; i < num_of_ver; i++)
		{
			dfs_ds->marked[i] = FALSE;
			dfs_ds->edge_to[i] = -1;
		}
	}
	
	/* Mark visited vertex as TRUE in DFS data structure */
	dfs_ds->marked[src_vertex] = TRUE;
#if DEBUG_ENABLE
	printf("\n >>>> Marked [src_vertex : %d]", src_vertex);
#endif

	/* Get Iterator of adjacent vertices to vertice-"src_vertex" */
    adjacent_vertex_iterator = adjacent(graph_instance, src_vertex);
#if DEBUG_ENABLE
	print_adjacent(graph_instance, src_vertex);
#endif

	/* Iterate through adjacent vertexes of src_vertex */
	while(adjacent_vertex_iterator != NULL)
	{
		int w = adjacent_vertex_iterator->vertex_num;
		
		/* if this node is not visited, 
		call DFS recursively for this adjacent node, 
		till we reach a marked node */
		if(!dfs_ds->marked[w])
		{
			dfs(graph_instance, w);
			dfs_ds->edge_to[w] = src_vertex;
#if DEBUG_ENABLE			
			printf("\n >>>>>> edge_to [w : %d] = [src_vertex : %d]", w, src_vertex);
#endif
		}
		adjacent_vertex_iterator = adjacent_vertex_iterator->next;
	}
}


/* Is there a path to dst_vertex ? 
If "marked" is TRUE, that means that vertex can be reached. 
This API should be called immediately after DFS routine */
bool has_path(int dst_vertex)
{
	bool marked = FALSE;
	
	if(dfs_ds)
	{
		return dfs_ds->marked[dst_vertex];
	}
	
	return marked;	
}

/* path from src_vertex to dst_vertex, NULL if no such path */
linked_list_t * path_to(int src_vertex, int dst_vertex)
{
	linked_list_t *head = NULL, *temp = NULL;
	/* If destination vertex is 
	not visited (ie. FALSE), that means there is not valid 
	path to destination vertex */
	if(has_path(dst_vertex) == FALSE)
	{
		return NULL;
	}
	
	/* Start creating a linked list to store path */
	head = create_new_node(dst_vertex);
	
	/* Keep adding the vertexes in path to iterator */
	while(dfs_ds->edge_to[dst_vertex] != src_vertex)
	{
		temp = create_new_node(dfs_ds->edge_to[dst_vertex]);
		temp->next = head;
		head = temp;
		
		/* Get the parent vertex to current vertex */
		dst_vertex = dfs_ds->edge_to[dst_vertex];
	}
	
	/* Add the source vertex */
	temp = create_new_node(src_vertex);
	temp->next = head;
	head = temp;
	
	return head;
}

int main()
{
	int i = 0, vertices = 0, edges = 0, adj_vertex = 0;
	int v1 = 0, v2 = 0;
	int src_vertex = 0; 
	int dst_vertex = 3;
	graph_t * graph_instance = NULL;
	linked_list_t * path_iterator = NULL;
	
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
	
#if 0
	// Print adjacent list of vertex
	printf("\nEnter the Vertex for which adjacent Vertex are required : ");
	scanf("%d", &adj_vertex);
    print_adjacent(graph_instance, adj_vertex);
#endif 

    // Print max degree of graph
    printf("\n=======================================================");
    printf("\nMax Degree of Graph : %d", max_degree(graph_instance) );
    printf("\n=======================================================");

    // Count number of self loops in graph
    printf("\n=======================================================");
    printf("\nSelf Loops in Graph : %d", number_of_self_loops(graph_instance) );
    printf("\n=======================================================");

	printf("\n=======================================================");
    dfs(graph_instance, src_vertex);
	printf("\nPath to vertex(%d) till vertex (%d) : ", src_vertex , dst_vertex);
	path_iterator = path_to(src_vertex, dst_vertex);
	if(path_iterator)
	{
	    while(path_iterator != NULL)
    	{
    		printf("%d -> ", path_iterator->vertex_num);
    		path_iterator = path_iterator->next;
    	}
	}
	else
	{
	    printf(" No path.");
	}
    printf("\n=======================================================");

	
	
	getch();
    return 0;
}
