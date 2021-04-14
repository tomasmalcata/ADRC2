#include "alg.h"
#include "stats.h"

int main(int argc, char *argv[])
{

	int as1, as2, rel;
	int size = 65536;
	int AS;
	Graph* graph = InitGraph(size);
	printf("%d\n", graph[10].AS);
	FILE *file;

	if(argc != 2)
	{
		printf("Please insert program and file\n");
		exit(-1);
	}

	file = fopen(argv[1], "r");
	if(file == NULL){
		printf("The file does not exist\n");
		exit(-1);
	}

	while(1)
	{
		if(fscanf(file, "%d %d %d", &as1, &as2, &rel) != 3)
		{
			break;
		}
		//printf("%d %d %d\n", as1, as2, rel);
		addEdge(graph, as1, as2, rel);
	}

	fclose(file);


	if (check_all_cycles(graph))
	{
		printf("It has cycles\n");
	}
	else
		printf("It has not cycles\n");


	if (check_conectivity(graph))
	{
		printf("It is commercially connected\n");
	}
	else
		printf("It is not commercially connected\n");

	all_type_of_routes_w_size(graph);
	printf("all routes with type done\n");
	size_of_all_routes(graph);
	printf("all sizes done\n");
	Write_to_File(graph);

	free_graph(graph);
}
