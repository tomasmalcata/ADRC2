#include "heap.h"

heap acervo;
int MAX_SIZE = 65536;

void init_heap(){
  int i = 0;
  acervo.vals = (node*)malloc(MAX_SIZE*sizeof(node));
  acervo.mp = (int*)malloc(MAX_SIZE*sizeof(int));
  acervo.last = 0;
  for(i = 0; i < MAX_SIZE; i++){
    acervo.mp[i] = -1;
  }
}

int get_left_child(int parent){
  return 2*parent + 1;
}

int get_right_child(int parent){
  return 2*parent + 2;
}

int get_parent(int child){
  return (child - 1)/2;
}

int check_prior(int index1, int index2){
  //uses heap indexes
  //this function should return 1 if index1 is more prior and 0 if it is 2
  if((acervo.vals[index2].r > acervo.vals[index1].r) || (acervo.vals[index2].r == acervo.vals[index1].r && acervo.vals[index2].size > acervo.vals[index1].size))
    return 1;
  return 0;
}
void change(int index1, int index2){
  //THIS FUNCTION SHOULD PUT THE VALUES OF IND1 POS IN IND2
  //IT SHOULD ALSO UPDATE MP VECTOR VALUES
  node temp;
  temp = acervo.vals[index2];

  acervo.vals[index2] = acervo.vals[index1];
  acervo.vals[index1] = temp;

  acervo.mp[acervo.vals[index2].AS] = index2;
  acervo.mp[acervo.vals[index1].AS] = index1;
}

void FixItDown(int index){//where should we start fix
  int left = get_left_child(index);
  int right = get_right_child(index);
  int smallest = index;

  if(left < acervo.last && check_prior(left,index))
    smallest = left;
  if(right < acervo.last && check_prior(right,smallest))
    smallest = right;
  if(smallest != index){ //false if the heap is fixes
    change(smallest, index);
    FixItDown(smallest);
  }
}


void FixItUp(int index){ //where we should start fix
  while(index != 0 && check_prior(index, get_parent(index))){
    change(index, get_parent(index));
    index = get_parent(index);
  }
}

int RemovePrior(int *AS, int *type, int *size){
  //this function should return the head node
  //then fix the heap consition
  if(acervo.last == 0)
    return 0; //the heap is empty

  //passing the value out
  *AS = acervo.vals[0].AS;
  *type = acervo.vals[0].r;
  *size = acervo.vals[0].size;

  //change with the last node

  change(0, acervo.last - 1);
  //delete last
  acervo.mp[*AS] = -1;
  acervo.last -= 1;
  //fix heap condition

  FixItDown(0); //start from the HEAD
  return 1;
}

void Insert(int AS, int r, int s){
  //primeiro comparar com o que já está no acervo
  int index = acervo.mp[AS];
  //printf("index %d\n", index);
  if(index != -1){
    if(r > acervo.vals[index].r || (r == acervo.vals[index].r && s >= acervo.vals[index].size))
      return; //The queue has a more priority value

    //The function should change the value and fix the heap
    //fix upper values only
    //printf("Replace\n");
    acervo.vals[index].AS = AS;
    acervo.vals[index].r = r;
    acervo.vals[index].size = s;
    FixItUp(index);
  }
  else{
    //this function should insert in acervo.last pos
    //fix the heap

    //Insert in last
    //printf("New\n");
    acervo.vals[acervo.last].AS = AS;
    acervo.vals[acervo.last].r = r;
    acervo.vals[acervo.last].size = s;
    acervo.mp[AS] = acervo.last;
    FixItUp(acervo.last);
    acervo.last += 1;
  }
}

void free_heap(){
  free(acervo.vals);
  free(acervo.mp);
}

void PrintHeap()
{
  int i;
  printf("Heap size: %d\n", acervo.last);
  for(i = 0; i < acervo.last; i++){
    printf("%d - AS:%d r:%d size:%d\n", i, acervo.vals[i].AS, acervo.vals[i].r,acervo.vals[i].size);
  }
  printf("\n");
}