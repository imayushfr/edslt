# EDSA Assignment Q10: Smart Bridge Load Monitor Simulation

## Name: 
## Roll Number: ME24B10
## Date: 15/04/2025
### PROBLEM STATEMENT:
Designing a Smart Bridge Load Monitor to track bridge components (e.g., "Beam", "Cable", "Deck", "Pylon", "Joint") for safety.
### KEY OBJECTIVES:
•	Simulating load tests and monitor stress levels of bridge components.
•	Maintaining a log of recent load test results and handling overflow.
•	Updating status of stressed components after reinforcement.
•	Managing and tracking components which needs high-priority repairs in a cyclic order.
•	Using appropriate data structures in structural monitoring systems.
### DESIGN EXPLANATION:
#### Why These Data Structures ?
•	Queue: Components which added first, will be tested first.
•	Stack: Most recent stressed components are considered most urgent, needs immediate action.
•	Fixed-Size Array: Maintaining history of latest 6 load results, automatically overwriting old  entries.
•	Singly Linked List: Allows dynamic addition/removal of stressed components.
•	Doubly Linked List: Allows forward/backward traversal.
•	Circular Linked List: Allows cyclic traversal.
#### How they are efficient ?
•	Queue/Stack: O(1) for insert/remove.
•	Linked Lists: Dynamic, no reallocation needed.
•	Circular Linked List: Natural for repeated rounds without reset logic.
### LOGIC OF THE CODE:
#### Task 1: Load and Stress Test
•	Components are enqueued into a queue.
•	Urgent components are dequeued and pushed into a stack.
•	Stack is then popped to execute urgent tasks.
#### Task 2: Load History Unit
•	New load results are logged in a fixed array of 6 elements.
•	On overflow, the oldest entry is overwritten by shifting all entries left.

#### Task 3: Stressed Component Tracker
•	Components which are stressed added to a singly linked list.
•	Once reinforced, it is removed from stress list and added to a doubly linked list.
•	Traversals are done in both directions.
#### Task 4: Priority Repairs
•	Components which needs urgent action are added to a circular linked list.
•	Traversed multiple times to simulate periodic monitoring.
### KEY VARIABLES AND FUNCTIONS:
#### Task 1: Load and Stress Test Variables:
•	Cqueue: Circular queue to manage incoming missions.
•	Stack: Stack to prioritize urgent missions.
Functions:
•	init_queue(), init_stack(): Initialize queue and stack pointers.
•	enqueue(): Add a robot to the mission queue.
•	dequeue(): Remove a robot from the mission queue.
•	push(): Push a robot into the urgent stack.
•	pop(): Pop a robot out of the urgent stack.
________________________________________
#### Task 2: Load History Unit Variables:
•	Log: Stores the rescue mission history in a fixed-size array
Functions
•	init_log(): Initializes the log counter.
•	log_mission(): Adds a new mission to the log and if full, then removes the oldest one by shifting the array.
________________________________________
#### Task 3:  Stressed Component Tracker
Variables:
•	singly_node: Node of singly linked list for damaged robots.
•	doubly_node: Node of doubly linked list for repaired robots.
Functions:
•	createsingly(): Allocates and initializes a new damaged robot node.
•	insert_damaged(): Adds a damaged robot to the end of the singly linked list.
•	remove_damaged(): Removes a damaged robot from the list when repaired.
•	create_doubly(): Allocates and initializes a new repaired robot node.
•	insert_repaired(): Adds a robot to the doubly linked list.
•	traverse_forward(): Traverses repaired robot list forward.
•	traverse_backward(): Traverses repaired robot list backward.
________________________________________
#### Task 4: Priority Repairs
Variables:
•	circular_node: Node of circular linked list for priority redeployment.
Functions:
•	create_circular(): Creates a new circular list node.
•	insert_priority(): Adds a robot to the circular list.
•	traverse_circular(): Cycles through the priority redeployment list for a given number of rounds.
### ANSWERS TO CREATIVITY QUESTIONS
#### Q1. Why LIFO fits here ?
LIFO is appropriate for stress checks because the last component tested (the Bolt) might be crucial for holding other components together. If the Bolt fails, other components might be at risk regardless of their condition. Checking the most recent concerns first ensures critical connections are addressed before analyzing individual components. 
#### Q2. Reason for archiving: 
Archiving the oldest load test results is essential for maintaining compliance with infrastructure safety regulations that require historical data retention. This enables engineers to track structural degradation patterns over time while focusing on recent readings for immediate safety decisions. 
#### Q3. Stress cause and fix: 
The Cable exhibited stress due to excessive vibration from high winds and heavy traffic loads. The reinforcement involved installing advanced dampers to absorb vibration and applying carbon fiber wrapping to strengthen the cable without adding significant weight, thus extending its service life by 15-20 years.

#### Q4. Repair Tweak: 
The Pylon repair was enhanced with a smart sensor network that continuously monitors micro-movements and temperature variations. This adaptive system automatically adjusts internal tension cables during extreme weather events, providing real-time data to maintenance crews and allowing for preventive intervention before structural issues develop.  
## CODE:
// Name: 
// Roll Number: ME24B10

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


## SAMPLE OUTPUT:
 PS C:\Users\AYUSH GUPTA\Desktop\c> gcc edsa.c
PS C:\Users\AYUSH GUPTA\Desktop\c> ./a
Scanner enqueued.
Digger enqueued.
Lift enqueued.
Light enqueued.
Drone enqueued.
Cutter enqueued.

Scanner pushed.
Digger pushed.
Lift pushed.
Light pushed.
Drone pushed.
Cutter pushed.

Executing urgent tasks: Cutter
Executing urgent tasks: Drone
Executing urgent tasks: Light
Executing urgent tasks: Lift
Executing urgent tasks: Digger
Executing urgent tasks: Scanner

Mis1 logged (0)
Mis2 logged (1)
Mis3 logged (2)
Mis4 logged (3)
Mis5 logged (4)
Mis6 logged (5)

Reporting oldest mission: Mis1
Mis7 logged (5)

Reporting oldest mission: Mis2
Mis8 logged (5)

0. Mis3
1. Mis4
2. Mis5
3. Mis6
4. Mis7
5. Mis8

Damaged robot: Digger added to repair list
Damaged robot: Drone added to repair list

Digger robot removed from damaged list
Repaired robot: Digger added to inspection list

Forward traversal: Digger -> NULL
Backward traversal: Digger -> NULL

Scanner robot added to priority redeployment list
Lift robot added to priority redeployment list

Traversing priority robots (2 rounds):
Checking: Scanner
Checking: Lift
Completed 1 round(s)

Checking: Scanner
Checking: Lift
Completed 2 round(s)
