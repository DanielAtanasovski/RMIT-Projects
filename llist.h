/* llist.h
 * Generic Linked List
 * 
 * Sourced from:
 * https://gist.github.com/meylingtaing/11018042
 */

struct node {
    void *data;
    struct node *next;
};

typedef struct node * llist;

// Additions by Daniel Atanasovski s3658474
// ---

// Gets size of list
int llist_getSize(llist *list);

// Returns a specific node within a specific position of a list
struct node *llist_getNode(llist *list, int position);

// Returns the data of a specific node within a specific position of a list
void *llist_get(llist *list, int position);

// Removes a specific node within a specific position of a list and returns it
void *llist_popAt(llist *list, int position);

// --- end additions

/* llist_create: Create a linked list */
llist *llist_create(void *data);

/* llist_free: Free a linked list */
void llist_free(llist *list);

/* llist_add_inorder: Add to sorted linked list */
int llist_add_inorder(void *data, llist *list, 
                       int (*comp)(void *, void *));

/* llist_push: Add to head of list */
void llist_push(llist *list, void *data);

/* llist_pop: remove and return head of linked list */
void *llist_pop(llist *list);

/* llist_print: print linked list */
void llist_print(llist *list, void (*print)(void *data));
