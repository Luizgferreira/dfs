#ifndef _TRAB_H
#define _TRAB_H

struct node{
    int value;
    int visited;
    struct node * next;
};

struct node * start_node(int value);
void insert_next(struct node * cur_node, int value);
int search(struct node * graph[], int n);
int dfs_max(struct node * graph[], int n, int index, int visited_index[]);
void set_visited(struct node * graph[], int n);
void free_node(struct node * cur_node);
void free_graph(struct node * graph[], int n);
#endif