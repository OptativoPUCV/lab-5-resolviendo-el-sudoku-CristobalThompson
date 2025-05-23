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
      int diccionarioF[10] = {0};
      int diccionarioC[10] = {0};
      int diccionarioSub[10] = {0};

      for(int pos = 0; pos < 9; ++pos){
        int valorF = n->sudo[indice][pos];
        int valorC = n->sudo[pos][indice];
      
          if (diccionarioF[valorF] == 0)
            diccionarioF[valorF] = valorF;
          else return 0;

          if (diccionarioC[valorC] == 0)
            diccionarioC[valorC] = valorC;
          else return 0;
      }

      for(int p = 0; p < 9; ++p){
        int i=3*(indice/3) + (p/3);
        int j=3*(indice%3) + (p%3);
        int valorSub = n->sudo[i][j];

        if (diccionarioSub[valorSub] == 0)
            diccionarioSub[valorSub] = valorSub;
        else return 0;
      }
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
      if (is_valid(new))
        pushBack(list, new);
    }

    return list;
}


int is_final(Node* n){
    for(int k = 0; k < 9; ++k){
      for(int j = 0; j < 9; ++j){
        if (n->sudo[k][j] == 0)
          return 0;
      }
    }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* pila = createStack();
  push(pila, initial);
  while(top(pila) != NULL){
    Node* arriba = top(pila);
    pop(pila);
    ++(*cont);
    if (is_final(arriba))return arriba;
    List* adj = get_adj_nodes(arriba);
    Node* aux = first(adj);
    while(aux != NULL){
      push(pila, aux);
      aux = next(adj);
    }
    free(arriba);
  }
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