#include <graph.h>

#include <assert.h>
#include <benchmark.h>
#include <queue.h>
#include <stack.h>
#include <macros.h>
#include <math.h>

// Private
struct graph {
	int V;
	bool **adjM;
};

graph_Opt graph_Print;
graph_Opt graph_AllPaths;

static void dfs (int V, bool **adjM, int from, bool visited[]) {

	if (graph_Print == graph_OptYes)
		printf ("%d ", from);

	bool *adj = adjM[from];
	for (int to = 0; to < V; ++to)
		if (adj[to] && !visited[to]) {
			visited[to] = true;
			dfs(V, adjM, to, visited);
		}
};

static void dfsPath (
	int V, bool **adjM, int from, bool visited[], stack_t path) {

	Stack.push(path, from);

	bool end = true;

	bool *adj = adjM[from];
	for (int to = 0; to < V; ++to)
		if (adj[to] && !visited[to]) {
			end = false;
			visited[to] = true;
			dfsPath(V, adjM, to, visited, path);
		
			if (graph_AllPaths == graph_OptYes)
				visited[to] = false;
		}
	
	if (end && graph_Print == graph_OptYes) {
		void print(int x) { printf("%d ", x); }
		Stack.walk(path, print);
		putchar('\n');
	}

	Stack.pop(path);
};

// Constructors/Destructors
graph_t graph_new (int V) {
	graph_t graph = malloc(sizeof(struct graph));
	
	graph->adjM = malloc(sizeof(bool *) * V);
	for (int i = 0; i < V; ++i) {
		graph->adjM[i] = malloc(sizeof(bool) * V);
		memset(graph->adjM[i], false, V);
	}

	graph->V = V;
	
	return graph;
}

graph_t graph_delete (graph_t G) {
	int V = G->V;
	
	for (int i = 0; i < V; ++i)
		free(G->adjM[i]);
	
	free(G->adjM);
	free(G);

	return NULL;
}

// Métodos
bool graph_isConnected (graph_t G) {
	int V = G->V;
	bool visited[V]; memset(visited, false, V);

	graph_Opt Print_backup = graph_Print;
	graph_Print = graph_OptNo;

	visited[0] = true;
	dfs(V, G->adjM, 0, visited);

	graph_Print = Print_backup;

	for (int i = 0; i < V; ++i)
		if (!visited[i])
			return false;
	
	return true;
}

void graph_fprint (graph_t G, FILE *fptr) {
	int V = G->V;
	bool **adjM = G->adjM;

	char str[10];
	int n_zeros = (int) ceil(log10(V));
	sprintf(str, "%%0%dd = ", n_zeros);

	for (int i = 0; i < V; ++i) {
		bool *adj = adjM[i];
		
		fprintf(fptr, str, i);
		
		for (int j = 0; j < V; ++j)
			if (adj[j])
				fprintf(fptr, "%d ", j);
		putc('\n', fptr);
	}
}

void graph_push (graph_t G, edge_t e) {
	G->adjM[e.x][e.y] = G->adjM[e.y][e.x] = true;
}

void graph_randomize (graph_t G, float connectivity) {
	int V = G->V;
	bool **adjM = G->adjM;

	int E = ((V * (V - 1)) / 2) * connectivity;
	if (E < (V - 1))
		E = V - 1;

	do {
		for (int i = 0; i < V; ++i)
			memset(adjM[i], false, V);

		for (int e = 0; e < E; ++e) {
			int x, y;
			do { x = benchmark_brand(0, V); y = benchmark_brand(0, V); }
			while (x == y || adjM[x][y] || adjM[y][x]);
			adjM[x][y] = adjM[y][x] = true;
		}

	} while (!graph_isConnected(G));

	if (graph_Print == graph_OptYes)
		graph_fprint(G, stdout);
}

// Caminhamentos
void graph_bfs (graph_t G, int from) {
	int V = G->V;
	bool **adjM = G->adjM;
	bool visited[V]; memset(visited, false, V);
	queue_t queue = Queue.new(V*V);

	visited[from] = true;
	Queue.push(queue, from);
	while (Queue.size(queue)) {
		from = Queue.top(queue); Queue.pop(queue);

		char clean = true;
		if (graph_Print == graph_OptYes)
			printf("nó %02d: ", from);

		bool *adj = adjM[from];
		for (int to = 0; to < V; ++to)
			if (adj[to] && !visited[to]) {
				visited[to] = true;
				Queue.push(queue, to);
				if (graph_Print == graph_OptYes)
					printf("%d ", to);
				clean = false;
			}
		
		if (graph_Print == graph_OptYes) {
			if (clean) printf("%c[2K\r", 27);
			else putchar('\n');			
		}
	}
}

void graph_dfs (graph_t G, int from) {
	int V = G->V;
	bool visited[V]; memset(visited, false, V);

	visited[from] = true;
	dfs(V, G->adjM, from, visited);

	if(graph_Print == graph_OptYes)
		putchar('\n');
}

void graph_paths (graph_t G, int from) {
	int V = G->V;
	bool visited[V]; memset(visited, false, V);

	stack_t path = Stack.new(V+1);
	visited[from] = true;
	dfsPath(V, G->adjM, from, visited, path);
	path = Stack.delete(path);
}