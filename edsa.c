// Name: Ayush Gupta
// Roll Number: ME24B1076

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max 6
#define name 8

// Task 1: Mission and Urgency
typedef struct {
    char robo[max][name];
    int fr;
    int rr;
} Cqueue;  // Circular queue for missions

typedef struct {
    char robo[max][name];
    int top;
} Stack;  // Stack for urgent missions

// For circular queue
void init_queue(Cqueue *q) 
{
    q->fr = -1;
    q->rr = -1;
}

int queue_full(Cqueue *q) 
{
    return (q->rr + 1) % max == q->fr;
}

int queue_empty(Cqueue *q) 
{
    return q->fr == -1;
}

void enqueue(Cqueue *q, char *robo) 
{
    if (queue_full(q))
    {
        printf("Queue overflow!\n");
        return;
    }
    else if (queue_empty(q))
    {
        // Intialize both to 0
        q->fr = 0;
        q->rr = 0;
    }
    else
    {
        q->rr = (q->rr + 1) % max;
    }
    strcpy(q->robo[q->rr], robo);  // Copying strings
    printf("%s enqueued.\n", robo);
}

char* dequeue(Cqueue *q) 
{
    if (queue_empty(q))
    {
        printf("Queue underflow!\n");
        return "";
    }

    char *robo = q->robo[q->fr];

    if (q->fr == q->rr) // Its the last element
    {
        q->fr = -1;
        q->rr = -1;
    }
    else
    {
        q->fr = (q->fr + 1) % max;
    }
    return robo;
}

// For stack
void init_stack(Stack *s) 
{
    s->top = -1;
}

int stack_empty(Stack *s) 
{
    return s->top == -1;
}

int stack_full(Stack *s) 
{
    return s->top == max - 1;
}

void push(Stack *s, char *robo) 
{
    if (stack_full(s))
    {
        printf("Stack overflow!\n");
        return;
    }

    s->top++;
    strcpy(s->robo[s->top], robo);
    printf("%s pushed.\n", robo);
}

char* pop(Stack *s) 
{
    if (stack_empty(s))
    {
        printf("Stack underflow!\n");
        return "";
    }

    char *robo = s->robo[s->top];
    s->top--;
    return robo;
}

// Executing task 1
void mission_and_urgency() 
{
    Cqueue q;
    Stack s;

    init_queue(&q);
    init_stack(&s);

    enqueue(&q, "Scanner");
    enqueue(&q, "Digger");
    enqueue(&q, "Lift");
    enqueue(&q, "Light");
    enqueue(&q, "Drone");
    enqueue(&q, "Cutter");
    printf("\n");

    while (!queue_empty(&q)) 
    {
        // Dequeue and push urgent tasks
        push(&s, dequeue(&q));
    }
    printf("\n");

    while (!stack_empty(&s)) 
    {
        printf("Executing urgent tasks: %s\n", pop(&s));
    }
    printf("\n");
}


// Task 2: Rescue log unit
typedef struct {
    char missions[max][name];
    int counter;
} Log;

void init_log(Log *log) 
{
    log->counter = 0;
} 

void log_mission(Log *log, char *mission) 
{
    if (log->counter < 6) 
    {
        strcpy(log->missions[log->counter], mission);
        printf("%s logged (%d)\n", mission, log->counter);
        log->counter++;
    }
    else  // If array is full
    {
        printf("\nReporting oldest mission: %s\n", log->missions[0]);
        log->counter--;

        for (int i = 0; i < max - 1; i++)  // Shift all missions to left
        {
            strcpy(log->missions[i], log->missions[i + 1]);
        }

        strcpy(log->missions[max - 1], mission);  // Add to last
        printf("%s logged (%d)\n", mission, log->counter);
        log->counter++;
    }
}

// Executing task 2
void rescue_log() 
{
    Log log;
    init_log(&log);

    log_mission(&log, "Mis1");
    log_mission(&log, "Mis2");
    log_mission(&log, "Mis3");
    log_mission(&log, "Mis4");
    log_mission(&log, "Mis5");
    log_mission(&log, "Mis6");

    log_mission(&log, "Mis7");
    log_mission(&log, "Mis8");

    printf("\n");
    for (int i = 0; i < max; i++) 
    {
        printf("%d. %s\n", i, log.missions[i]);
    }
    printf("\n");
}

// Task 3: Damaged robot tracker
typedef struct singly_node {
    char damaged[name];
    struct singly_node *next;
} singly_node;

typedef struct doubly_node {
    char repaired[name];
    struct doubly_node *prev;
    struct doubly_node *next;
} doubly_node;

// For damaged robots
singly_node* createsingly(char *damaged) 
{
    singly_node *new_node = (singly_node *)malloc(sizeof(singly_node));
    strcpy(new_node->damaged, damaged);
    new_node->next = NULL;
    return new_node;
}

void insert_damaged(singly_node **head, char *damaged) 
{
    singly_node *new_node = createsingly(damaged);

    if (*head == NULL) 
    {
        *head = new_node;
    } 
    else 
    {
        singly_node *temp = *head;
        while (temp->next != NULL) 
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    printf("Damaged robot: %s added to repair list\n", damaged);
}

singly_node* remove_damaged(singly_node **head, char *damaged) 
{
    if (*head == NULL) 
    {
        return NULL;
    }
    
    singly_node *current = *head;
    singly_node *prev = NULL;
    
    // If head node has the robot to be removed
    if (strcmp(current->damaged, damaged) == 0)
    {
        *head = current->next;
        printf("%s robot removed from damaged list\n", damaged);
        return current;
    }

    // If not, then searching
    while (current != NULL && strcmp(current->damaged, damaged) != 0) 
    {
        prev = current;
        current = current->next;
    }

    // Even if not found
    if (current == NULL) 
    {
        printf("%s robot not found in damaged list\n", damaged);
        return NULL;
    }

    prev->next = current->next;
    printf("%s robot removed from damaged list\n", damaged);
    return current;
}

// For repaired robots
doubly_node* create_doubly(char *repaired) 
{
    doubly_node *new_node = (doubly_node *)malloc(sizeof(doubly_node));
    strcpy(new_node->repaired, repaired);
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

void insert_repaired(doubly_node **head, char *repaired) 
{
    doubly_node *new_node = create_doubly(repaired);
    
    if (*head == NULL) 
    {
        *head = new_node;
    } 
    else 
    {
        doubly_node *temp = *head;
        while (temp->next != NULL) 
        {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->prev = temp;
    } 
    printf("Repaired robot: %s added to inspection list\n", repaired);
}

void traverse_forward(doubly_node *head) 
{
    printf("Forward traversal: ");
    doubly_node *temp = head;
    while (temp != NULL) 
    {
        printf("%s -> ", temp->repaired);
        temp = temp->next;
    }
    printf("NULL\n");
}

void traverse_backward(doubly_node *head) 
{
    if (head == NULL) 
    {
        printf("Backward traversal: NULL\n");
        return;
    }

    doubly_node *temp = head; // First, find last node
    while (temp->next != NULL) 
    {
        temp = temp->next;
    }

    printf("Backward traversal: ");
    while (temp != NULL) 
    {
        printf("%s -> ", temp->repaired);
        temp = temp->prev;
    }
    printf("NULL\n");
}

// Executing task 3
void damaged_robot_tracker() 
{
    singly_node *damaged_robots = NULL;
    doubly_node *repaired_robots = NULL;
    
    insert_damaged(&damaged_robots, "Digger");
    insert_damaged(&damaged_robots, "Drone");
    printf("\n");
    
    singly_node *repaired = remove_damaged(&damaged_robots, "Digger");
    if (repaired != NULL) 
    {
        insert_repaired(&repaired_robots, repaired->damaged);
        free(repaired);  // Free node the transferring data
    }

    printf("\n");
    traverse_forward(repaired_robots);
    traverse_backward(repaired_robots);
    printf("\n");
}

// Task 4: Priority redeployment
typedef struct circular_node {
    char urgent[name];
    struct circular_node *next;
} circular_node;

circular_node* create_circular(char *urgent) 
{
    circular_node *new_node = (circular_node *)malloc(sizeof(circular_node));
    strcpy(new_node->urgent, urgent);
    new_node->next = NULL;
    return new_node;
}

void insert_priority(circular_node **head, char *urgent) 
{
    circular_node *new_node = create_circular(urgent);
    
    if (*head == NULL) 
    {
        *head = new_node;
        new_node->next = new_node;  // Points to itself
    } 
    else 
    {
        circular_node *temp = *head;
        while (temp->next != *head) 
        {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->next = *head;
    }
    printf("%s robot added to priority redeployment list\n", urgent);
}

void traverse_circular(circular_node *head, int rounds) 
{
    if (head == NULL) 
    {
        printf("Priority list is empty\n");
        return;
    }

    circular_node *temp = head;
    int nodes = 0;
    int count = 0;

    do  // Conuting number of nodes
    {
        nodes++;
        temp = temp->next;
    } while (temp != head);
    
    temp = head;
    
    printf("Traversing priority robots (%d rounds):\n", rounds);
    do 
    {
        printf("Checking: %s\n", temp->urgent);
        temp = temp->next;
        count++;
        
        if (count % nodes == 0)  // Rounds completed
        {
            printf("Completed %d round(s)\n\n", (count / nodes));
        }
        
    } while (count < rounds * nodes);
}

// Executing task 4
void priority_redeployment() 
{
    circular_node *priority_robots = NULL;
    
    insert_priority(&priority_robots, "Scanner");
    insert_priority(&priority_robots, "Lift");
    printf("\n");
    
    traverse_circular(priority_robots, 2);
}


int main() 
{
    mission_and_urgency();
    rescue_log();
    damaged_robot_tracker();
    priority_redeployment();
    return 0;
}