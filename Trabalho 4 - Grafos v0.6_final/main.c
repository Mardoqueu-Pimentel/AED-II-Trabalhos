#include <stdio.h>

#include <graph.h>
#include <benchmark.h>

int main(int argc, char const *argv[])
{
	benchmark_seed_rand();
	graph_Print = graph_OptYes;
	graph_AllPaths = graph_OptYes;

	printf("Quantidade de Vértices?\n");
	int V; scanf("%d", &V); putchar('\n');
	graph_t graph = graph_new(V);

	void (*search[])(graph_t, int) = { 
		graph_bfs, graph_dfs, graph_paths 
	};
	char *search_name[] = { "BFS", "DFS", "PATHS" };

	benchmark_times_t t[3];
	for (int i = 0; i < 3; ++i)
		t[i] = benchmark_times_new();

	for (int it = 0; it < 30; ++it) {
		
		float connectivity = benchmark_brand_double(0.3, 1.0);
		printf(
			"%02d: Grafo com %3d vértices | %3.0f%% de conexão\n", 
			it, V, connectivity * 100
		);
		graph_randomize(graph, connectivity); putchar('\n');

		char gname[10]; sprintf(gname, "it-%d", it);
		FILE *f = fopen(gname, "w+");
		graph_fprint(graph, f);
		fclose(f);

		int from = benchmark_brand(0, V);
		for (int sch = 0; sch < 3; ++sch) {
			printf("memory::%lld\n", benchmark_memory(BEFORE));

			printf("Busca: %s partindo de: %d\n", search_name[sch], from);
			benchmark_gettime();
			search[sch](graph, from);
			benchmark_times_update(&t[sch], benchmark_gettime());
			printf("tempo: %.4lf ms\n", search_name[sch], from, t[sch].last);
			
			putchar('\n');
		}
		
		int N = 10; while(--N) putchar('\n');
	}

	for (int sch = 0; sch < 2; ++sch) {
		printf(search_name[sch]);
		printf(
			": Méd: %.2lf ms | Men: %.2lf | Mai: %.2lf | Tot: %.2lf\n", 
			t[sch].mean, t[sch].lower, t[sch].bigger, t[sch].sum);
	}

	system("python3 MakeGraph.py");

	return 0;
}