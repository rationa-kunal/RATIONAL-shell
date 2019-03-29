
// command struct with ony argv
struct command{
    char *argv[128];
};

// Generic node for queue
struct node{
    void *entity;
    struct node *nxt;
    struct node *prev;
};

// Generic queue
struct queue{
    struct node *head;
    struct node *tail;
};
struct node *new_node(void *entry){
    struct node *n = (struct node *) malloc(sizeof(struct node));
    n->entity = entry;
    n->nxt = n->prev = NULL;
    return n;
}
struct queue *q_init(){
    struct queue *q = (struct queue *) malloc(sizeof(struct queue));
    q->head = NULL;
    q->tail = NULL;
}
void enqueue(struct queue *q, void *entry){
    if(q->head==NULL){
        q->head = new_node(entry);
        q->tail = q->head;
        return;
    }
    struct node *n = new_node(entry);
    n->nxt = q->head;
    q->head->prev = n;
    q->head = n;
}
void * dequeue(struct queue * q){
    struct node *t = q->tail;
    if(t==NULL){
        return NULL;
    }

    if(t->prev == NULL){
        q->head = NULL;
        q->tail = NULL;
        return t->entity;
    }
    t->prev->nxt = NULL;
    q->tail = t->prev;
    return t->entity;
}
bool is_empty(struct queue *q){
    return q->tail==NULL;
}