#include <stdio.h>
#include <stdlib.h>

struct node{
    int value;
    int visited;
    struct node * next;
};
struct node * start_node(int value);
void insert_next(struct node * cur_node, int value);

int search(struct node * graph[], int n);
int dfs_max(struct node * graph[], int n, int index, int visited_index[]);

void insert_next(struct node * cur_node, int value){
    struct node * new_node = start_node(value);
    while (cur_node->next != NULL){
        cur_node = cur_node->next;
    }
    cur_node->next = new_node;
}

struct node * start_node(int value){
    struct node * new_node = (struct node*)malloc(sizeof(struct node));
    new_node->value = value;
    new_node->visited = 0;
    new_node->next = NULL;
    return new_node;
}

void show_node(struct node * new_node){
    printf("value: %d\n", new_node->value);
    printf("visited: %d\n", new_node->visited);
    if(new_node->next != NULL){
        printf("dependencies: \n");
        show_node(new_node->next);
    }
}

int dfs_max(struct node * graph[], int n, int index, int visited_index[]){
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
    graph[index]->visited = -1;
    return max_depth+1;
}

void set_visited(struct node * graph[], int n){
    for(int i = 0; i < n; i++){
        graph[i]->visited = 0;
    }
}

int search(struct node * graph[], int n){
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

void main(){
    int n;
    scanf("%d", &n);
    struct node * graph[10];
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
    
}