typedef struct Stack 
{
	int *data; // this is a pointer to the start of the data for the stack
	int *top; // this will point to the next place to insert in the stack
	int capacity; // this is the maximal size of the stack
} Stack;

Stack *stk_create(int capacity);

int stk_empty(Stack *s);

int stk_full(Stack *s);

void stk_push(Stack *s, int value);

int stk_peek(Stack *s);

int stk_pop(Stack *s);

void stk_display(Stack *s, int reverse);

void stk_destroy(Stack *s);

Stack *stk_copy(Stack *s);