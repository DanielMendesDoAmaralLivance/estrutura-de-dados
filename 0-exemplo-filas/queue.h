typedef struct Queue_ Queue;

Queue* create_queue();
int inserting(Queue* queue, int value);
int removing(Queue* queue, int* value);
int next(Queue* queue, int* value);
void free_queue(Queue* queue);