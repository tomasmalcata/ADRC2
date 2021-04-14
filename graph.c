#include "graph.h"

int N = 0;

int max = 0;
Graph* InitGraph(int size){
	Graph* graph;
	N = size;
	int i = 0;
	graph = (Graph* ) malloc(N * sizeof(Graph));
	if (graph == NULL) {
			    printf("Memory error\n");
			    exit(-1);
  			}
	printf("%d\n", N);
	for(i = 0; i < N; i++){
		graph[i].AS = -1;
  		graph[i].type = -1;
  		graph[i].open = -1;
  		graph[i].visit = -1;
  		graph[i].peers = NULL;
  		graph[i].clients = NULL;
 		graph[i].providers = NULL;
	}
	return graph;
}

void createGraph(Graph* graph,int AS, int type)
{
  graph[AS].AS = AS;
  graph[AS].type = type;
  graph[AS].open = 0;
  graph[AS].visit = 0;
}


Succs* CreateSuccs(int AS)
{
  Succs* succs = (Succs*) malloc(sizeof(Succs));
  if (succs == NULL) {
			    printf("Memory error\n");
			    exit(-1);
  			}

  if (succs == NULL) {
    printf("Memory error\n");
    exit(-1);
  }
  succs->AS = AS;
  //succs->rel = rel;
  succs->next = NULL;

  return succs;
}



void InsertSucc(Graph *graph, int AS1, int AS2, int rel)
{
	Succs *aux = NULL;
	if(rel == 1){
		if(graph[AS1].clients == NULL){
		graph[AS1].clients = CreateSuccs(AS2);
		}
		else{
			aux = graph[AS1].clients;
			while(aux->next != NULL){
				aux = aux->next;
			}
			aux->next = CreateSuccs(AS2);
		}
	}

	if(rel == 2){
		if(graph[AS1].peers == NULL){
		graph[AS1].peers = CreateSuccs(AS2);
		}
		else{
			aux = graph[AS1].peers;
			while(aux->next != NULL){
				aux = aux->next;
			}
			aux->next = CreateSuccs(AS2);
		}
	}
	if(rel == 3){
		if(graph[AS1].providers == NULL){
		graph[AS1].providers = CreateSuccs(AS2);
		}
		else{
			aux = graph[AS1].providers;
			while(aux->next != NULL){
				aux = aux->next;
			}
			aux->next = CreateSuccs(AS2);
		}
	}
}

int get_new_type(int type, int rel){
	if(type == -1){
		if(rel == 1)
			return 1;
		if(rel == 2)
			return 1;
		if(rel == 3)
			return 3;
	}
	if(type == 1){
		if(rel == 1)
			return 1;
		if(rel == 2)
			return 1;
		if(rel == 3)
			return 2;
	}
	if(type == 2){
		return 2;
	}
	if(type == 3){
		if(rel == 1)
			return 2;
		if(rel == 2)
			return 3;
		if(rel == 3)
			return 3;
	}
}




void addEdge(Graph* graph, int AS1, int AS2, int rel)
{
	if(graph[AS2].AS == -1)
		createGraph(graph,AS2, -1);
	
	if(graph[AS1].AS == -1){
		createGraph(graph,AS1, get_new_type(-1,rel));
		InsertSucc(graph, AS1, AS2, rel);
	}
	else{
		graph[AS1].type = get_new_type(graph[AS1].type, rel);
		InsertSucc(graph, AS1,AS2, rel);
	}
}



//check if it is commercial connected
int get_n_T1(Graph* graph){
	int t1 = 0;
	int i;
	for(i = 0; i < N; i++){
		if(graph[i].type == 1){
			t1++;
		}
	}
	return t1;
}

int check_conectivity(Graph* graph){
	int T1 = get_n_T1(graph); // T1 -> Number of Tier-1s
	printf("T1:%d\n",T1);
	int i, count;
	Succs *aux = NULL;
	for(i = 0; i < N; i ++){
		if(graph[i].type == 1){
			count = 0;
			for (aux = graph[i].peers; aux != NULL; aux = aux->next){
				if (graph[aux->AS].type == 1)
					count++;
			}
			if(count != (T1 - 1))
				return 0;
		}
	}
	return 1;
}


int check_all_cycles(Graph* graph){
	int i = 0;
	for(i = 0; i < N; i++){
		if(graph[i].visit == 0 && graph[i].AS != -1)
			if(check_cycles(graph, i) == 1)
				return 1;
	}
	return 0;
}
int check_cycles(Graph* graph, int AS)
{
	int p = 0;
	Succs* aux;
	graph[AS].visit = 1;
	graph[AS].open = 1;
	int i;

	//printf("in %d\n", graph[AS].AS);

	for(aux = graph[AS].clients; (aux != NULL) && (p != 1); aux = aux->next){
		if(graph[aux->AS].open == 1){
			printf("cycle\n");
			return 1;
		}
		else if (graph[aux->AS].visit == 0)
			p = check_cycles(graph, aux->AS);
	}
	graph[AS].open = 0;
	return p;
}




/////////////////////////////////////
//FREE FUNCTIONS
///////////////////////////

void free_succs(Succs* succs)
{
  if (succs == NULL)
    return;
  free_succs(succs->next);
  free(succs);
}

void free_graph(Graph* graph)
{
	int i;
	for(i = 0; i < N; i++){
		free_succs(graph[i].clients);
  		free_succs(graph[i].providers);
  		free_succs(graph[i].peers);
	}

	free(graph);
}



/////////////////////////////////////
//AUX FUNCTIONS
///////////////////////////


void printSuccs(Succs* succs)
{

  Succs * aux = succs;
  int i = 0;
  while(aux != NULL){
  	i++;
  	printf(" %d ", aux->AS);
  	aux = aux->next;
  }
}

// A utility function to print the adjacency list
// representation of graph
void printGraph(Graph* graph)
{
	int i = 0;
 	printf("\n");
  	while(i < N) {
      	if(graph[i].AS != -1){
	      	printf("AS: %d, Type:%d\n", graph[i].AS, graph[i].type);
	      	printf("Clients:");
	      	if (graph[i].clients != NULL){
	        	printSuccs(graph[i].clients);
	      	}
	      	printf("\nPeers: ");
	        if (graph[i].peers != NULL){
	        	printSuccs(graph[i].peers);
	        }
	        printf("\nProviders: ");
	        if (graph[i].providers != NULL){
	        	printSuccs(graph[i].providers);
	        }
	        printf("\n\n");
		}
		i++;
	}
}
//auxiliar function
void print_nodes(Graph* graph)
{
	int i = 0;
	for(i = 0; i < N; i++){
		if(graph[i].AS == -1)
			continue;
		printf("AS:%d Type;%d\n", graph[i].AS, graph[i].type);
	}
}


