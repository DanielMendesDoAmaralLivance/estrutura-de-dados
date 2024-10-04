#include <stdlib.h>
#include "queue.h"
#include "..\nodo\single_node.h"
struct Queue_ {
    Node* begin;
    Node* end;
};

Queue* create_queue() {
    Queue* queue = (Queue *) malloc(sizeof(struct Queue_));
    if(queue != NULL) {
        queue->begin = NULL;
        queue->end = NULL;
    }
    return queue;
}	

int inserting(Queue* queue, int value) {
    Node* new_node = create_node(value);
    if(new_node == NULL) 
        return 0;
    if(queue->begin == NULL) {
        queue->begin = new_node;
    } else { 
        set_next(queue->end, new_node);
    }
    queue->end = new_node;
    return 1;
}

int removing(Queue* queue, int* value){
    if(queue->begin == NULL) 
        return 0;
    *value = get_data(queue->begin);
    Node* removed = queue->begin;
    queue->begin = get_next(queue->begin);
    free(removed);
    return 1;
}

int next(Queue* queue, int* value) {
	if(queue->begin == NULL) 
        return 0;
    *value = get_data(queue->begin);
	return 1;
}

void free_queue(Queue* queue) {
    Node* cursor = queue->begin;
    Node* removed;
    while(cursor != NULL) {
        removed = cursor;
        cursor = get_next(removed);
        free(removed);
    }
    free(queue);
}