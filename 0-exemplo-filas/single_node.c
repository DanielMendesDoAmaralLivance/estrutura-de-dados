#include "single_node.h"
#include <stdlib.h>

struct Node_ {
    int data;
    struct Node_ *next;
};

Node* create_node(int data) {
    Node* node = (Node*) malloc(sizeof(struct Node_));
    if(node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

Node* get_next(Node* node) {
    return node->next;
}

void set_next(Node* node, Node* node_next) {
    node->next = node_next;
}

int get_data(Node* node) {
    return node->data;
}

int set_data(Node* node, int value) {
    node->data = value;
}