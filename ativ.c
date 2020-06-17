#include <stdio.h>
#include <stdlib.h>
#include "trab.h"


int main(){
    int n;
    scanf("%d", &n);
    /*
    para facilitar o acesso aos nós, o grafo é representado como
    uma lista de ponteiros.
    */
    struct node * graph[n];
    for (int i = 0; i < n; i++){
        graph[i] = start_node(i); 
    }
    int d;
    scanf("%d", &d);
    int de, para;
    for (int i = 0; i < d; i++){
        scanf("%d %d", &de, &para);
        insert_next(graph[de], para);
    }
    int x = search(graph, n);
    printf("%d\n", x);
    free_graph(graph, n);
    return 0;
}