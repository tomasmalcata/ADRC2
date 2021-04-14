#include "stats.h"

int clients=0, peers=0, providers=0, total=0;
int MAX_STATS = 75;
// print to file stats

int *length_commercial = NULL;
int *length_shortest = NULL;

void initialize_vectors(){

  int i ;
  length_commercial = (int*) malloc(MAX_STATS * sizeof (int));
  length_shortest = (int*) malloc(MAX_STATS * sizeof (int));

  for (i = 0; i < MAX_STATS; i++){
    length_commercial[i] = 0;
    length_shortest[i] = 0;
  }
}

void update_vector_shortest(int size){
  length_shortest[size] += 1;
}
void write_percent(){
  FILE *f = fopen("counts.txt", "w");
  int total = clients + peers + providers;
  fprintf(f, "Client Routes: %f\n", (float)clients/total * 100);
  fprintf(f, "Peer Routes: %f\n", (float)peers/total * 100);
  fprintf(f, "Provider Routes: %f\n\n", (float)providers/total * 100);
  fprintf(stdout, "\nClient Routes: %f\n", (float)clients/total * 100);
  fprintf(stdout, "Peer Routes: %f\n", (float)peers/total * 100);
  fprintf(stdout, "Provider Routes: %f\n\n", (float)providers/total * 100);
  
  fclose(f);
}

void update_commercial_stats(int size, int type){
  length_commercial[size] += 1;
  if (type == 1)
    ++clients;
  else if (type == 2)
    ++peers;
  else if (type == 3)
    ++providers;
}

void sum_vects(){
  //this function turns the vector into a cumulative function
  int i = 0;
  for(i = (MAX_STATS-2); i >= 0; --i){
    length_commercial[i] += length_commercial[i+1];
    length_shortest[i] += length_shortest[i+1];
  }
}

void Write_to_File(Graph *graph){

  FILE *f = NULL, *p = NULL;

  f = fopen("commercial_stats.txt", "w");

  p = fopen("shortest_stats.txt", "w");

  if(f == NULL || p == NULL)
  {
      printf("Error opening file!\n");
      exit(1);
  }

  sum_vects();
  int i;
  for (i = 0; i < MAX_STATS; i++){
    fprintf(f, "%d,%d\n",i, length_commercial[i]);
    fprintf(p, "%d,%d\n",i, length_shortest[i]);
  }

  fclose(f);
  fclose(p);
  free(length_shortest);
  free(length_commercial);
}
