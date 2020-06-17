#include <stdio.h>
#include <stdlib.h>
#include "trab.h"

void insert_next(struct node * cur_node, int value){
    //insere um novo nó na lista de adjacência
    struct node * new_node = start_node(value);
    while (cur_node->next != NULL){
        cur_node = cur_node->next;
    }
    cur_node->next = new_node;
}

struct node * start_node(int value){
    //inicializa um nó com um valor definido e o valor inicial de visited (0)
    struct node * new_node = (struct node*)malloc(sizeof(struct node));
    new_node->value = value;
    new_node->visited = 0;
    new_node->next = NULL;
    return new_node;
}

int dfs_max(struct node * graph[], int n, int index, int visited_index[]){
    /*
    Essa função é responsável por fazer uma busca em profundidade a partir
    de um nó e retornar o maior caminho de suas conexões.
    Para cada nível, será retornada o maior caminho de suas conexões + 1 ou
    -1, no caso de encontrar um ciclo
    */
    graph[index]->visited = 1;
    visited_index[index] = 1;
    int max_depth = 0;
    struct node * next_node = graph[index]->next;
    while (next_node != NULL){
        int next_index = next_node->value;
        //identificar ciclo
        if(graph[next_index]->visited == 1){
            return -1;
        }
        int max_aux = dfs_max(graph, n, next_index, visited_index);
        if(max_aux == -1){
            return -1;
        }
        if(max_aux > max_depth){
            max_depth = max_aux;
        }
        next_node = next_node->next;
    }
    //o -1 no visited indica o nó "preto" das ilustrações
    graph[index]->visited = -1;
    return max_depth+1;
}

void set_visited(struct node * graph[], int n){
    //reinicia os valores de visited para uma nova busca
    for(int i = 0; i < n; i++){
        graph[i]->visited = 0;
    }
}

int search(struct node * graph[], int n){
    /*
    Função que buscará o maior caminho no grafo.
    Para isso, realizará busca saindo de todos os grafos não visitados
    em etapas posteriores.
    O vetor visited_index marca se o índice foi visitado.
    */
    int visited_index[n];
    int max_size = 0;
    for (int i = 0; i < n; i++){
        visited_index[i] = 0;
    }
    for (int i = 0; i < n; i++){
        if(visited_index[i] == 0){
            set_visited(graph, n);
            int max_aux = dfs_max(graph, n, i, visited_index);
            if(max_aux == -1){
                return -1;
            }
            if(max_aux > max_size){
                max_size = max_aux;
            }
        }
    }
    return max_size;
}

void free_node(struct node * cur_node){
    if(cur_node->next != NULL){
        free_node(cur_node->next);
    }
    free(cur_node);
    cur_node = NULL;
}

void free_graph(struct node * graph[], int n){
    for(int i = 0; i < n; i++){
        free_node(graph[i]);
    }
}