#include "alg.h"
#include "heap.h"
#include "stats.h"


void Initialized_visited(Graph *graph){
	int i;
	for (i = 0; i < N; ++i)
	{
		if(graph[i].AS == -1)
			continue;
		else
			graph[i].visit = -1;
	}
}



void type_of_routes_w_size(Graph* graph, int AS){
	int AS_test, type, size;
	Succs* aux;
	Insert(AS, 1, 0);
	int j = 0;
	//printf("\n %d - ", AS);
	while(RemovePrior(&AS_test, &type, &size)){
		if((graph[AS_test].visit) != AS){
			//printf("visit\n\n");
			j++;
			graph[AS_test].visit = AS;

			update_commercial_stats(size, type);

			printf("%d:%d(%d)-", AS_test, size, type);

			if(type == 1){
				for(aux = graph[AS_test].providers; aux != NULL; aux = aux->next){
					if(graph[aux->AS].visit == AS)
						continue;
					Insert(aux->AS, 1, size+1);
					//j++;
				}
				for(aux = graph[AS_test].peers; aux != NULL; aux = aux->next){
					if(graph[aux->AS].visit == AS)
						continue;
					Insert(aux->AS, 2, size+1);
					//j++;
				}
			}
			for(aux = graph[AS_test].clients; aux != NULL; aux = aux->next){
					if(graph[aux->AS].visit == AS)
						continue;
					Insert(aux->AS, 3, size+1);
					//j++;
				}
		}
		//printf("\n\n%d\n", j);
		//PrintOrderedList();
	}
	//printf("%d %d\n", AS,j);

}

void all_type_of_routes_w_size(Graph* graph){
	int i = 0;
	Initialized_visited(graph);
	initialize_vectors(); // Vetores length_shortest e length_commercial
	init_heap();
	/*for(i = 0; i < N; i++){
		if(graph[i].AS == -1)
			continue;

		//printf("\n\n%d!!!\n", i);	
		type_of_routes_w_size(graph, i);
		//PrintOrderedList();
	}*/
	type_of_routes_w_size(graph, 3);

	write_percent();
}



void size_of_routes(Graph* graph, int AS){
	//this function is almost te same without types (all 1)
	int AS_test, type, size;
	Succs* aux;
	Insert(AS, 1, 0);
	int j = 0;
	while(RemovePrior(&AS_test, &type, &size)){
		if((graph[AS_test].visit) != AS && (graph[AS_test].AS != -1)){
			//printf("visit\n\n");
			j++;
			graph[AS_test].visit = AS;
			update_vector_shortest(size);

			for(aux = graph[AS_test].providers; aux != NULL; aux = aux->next){
				if(graph[aux->AS].visit == AS)
					continue;
				Insert(aux->AS, 1, size+1);
				//j++;
			}
			for(aux = graph[AS_test].peers; aux != NULL; aux = aux->next){
				if(graph[aux->AS].visit == AS)
					continue;
				Insert(aux->AS, 1, size+1);
				//j++;
			}
			for(aux = graph[AS_test].clients; aux != NULL; aux = aux->next){
				if(graph[aux->AS].visit == AS)
					continue;
				Insert(aux->AS, 1, size+1);
				//j++;
			}
		}
		//printf("%d %d\n", AS, );
	}
	//printf("%d %d\n", AS,j);

}

void size_of_all_routes(Graph* graph){
	//this function runs type of routes in all AS except stubs without peers
	//stubs without peers will have 3 for every place

	int i = 0;;
	init_heap();
	Initialized_visited(graph);
	for(i = 0; i < N; i++){
		if(graph[i].AS == -1)
			continue;

		//printf("\n\n%d!!!\n", i);
		size_of_routes(graph, i);
	}
	free_heap();
}

