#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    for(int indice = 0; indice < 9; ++indice){
                            //0, 1, 2, 3, 4, 5, 6, 7, 8, 9 
      //int diccionarioF[10] = {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
      //int diccionarioC[10] = {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
      int diccionarioF[10] = {-1};
      int diccionarioC[10] = {-1};

      for(int pos = 0; pos < 9; ++pos){
        int valorF = n->sudo[indice][pos];
        int valorC = n->sudo[pos][indice];
        if (diccionarioF[valorF] == -1)
          diccionarioF[valorF] = valorF;
        else return 0;

        if (diccionarioC[valorC] == -1)
          diccionarioC[valorC] = valorC;
        else return 0;

      }
      if (diccionarioF[0] != -1 || diccionarioC[0] != -1)
        return 0;
    }
    return 1;         
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int fila = -1,col = -1;
    for(int k = 0; k < 9; ++k){
      for(int j = 0; j < 9; ++j){
        if (n->sudo[k][j] == 0){
          fila = k;
          col = j;
          break;
        }
      }
      if (fila != -1) break;
    }

    if (fila == -1) return list;

    for(int adj = 1; adj <= 9; ++adj){
      Node* new = copy(n);
      new->sudo[fila][col] = adj;
      pushBack(list, new);
    }

    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/