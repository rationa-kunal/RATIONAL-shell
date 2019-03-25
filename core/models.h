
struct command{
    char *argv[128];
};

struct node{
    void *entity;
    struct node *nxt;
    struct node *prev;
};

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

void enqueue(struct queue *q, struct command *cmd){
    if(q->head==NULL){
        q->head = new_node(cmd);
        q->tail = q->head;
        return;
    }
    struct node *n = new_node(cmd);
    n->nxt = q->head;
    q->head->prev = n;
    q->head = n;
}

struct command * dequeue(struct queue * q){
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