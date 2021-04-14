#ifndef _GRAPH_H
#define _GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Graph
{
  int AS;	//AS number
  int type; //-1 if does not have connections
  			//1 if tier1
  			//2 if in the middle
  			//3 if stub
  int visit; //aux for DFS
  int open;	 //aux for DFS
  //int *relation;	//1 client route
  					//2 peer route
  					//3 provider route
  struct Succs *clients; //p2c
  struct Succs *peers; //p2p
  struct Succs *providers; //c2p
} Graph;

typedef struct Succs
{
  int AS;
  struct Succs *next;
} Succs;

extern int N;

Graph* InitGraph(int size);
void createGraph(Graph* graph,int AS, int type);
void addEdge(Graph* graph, int AS1, int AS2, int rel);
void printSuccs(Succs* succs);
void print_nodes(Graph* graph);
void printGraph(Graph* graph);
void printPeers(Succs* succs);
void free_graph(Graph* graph);
int check_all_cycles(Graph* graph);
int check_cycles(Graph* graph, int AS);
int check_conectivity(Graph* graph);



#endif