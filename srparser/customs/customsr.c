#include<stdio.h>
#include<string.h>

struct Stack {
    int top;
    char array[100];
};

void push(struct Stack *stack, char item) { stack->array[++stack->top] = item; }
void pop(struct Stack *stack, int count) { stack->top -= count; }

void print(struct Stack *stack) { // print stack
    for (int i = 0; i <= stack->top; i++)
        if (stack->array[i] == 'i')
            printf("id");
        else
            printf("%c", stack->array[i]);
}

// Sr parser
// S->S+S
// S->S-S
// S->(S) 
// S->a

int reduce(struct Stack *stack) {
    int action = 0;
    int i = stack->top;
    if (i == -1) {
        return action;
    }
    if (stack->array[i] == 'a') { // E->id
        pop(stack, 1);
        push(stack, 'S');
        action = 1;
    } else if (stack->array[i] == 'S' && stack->array[i-1] == '+' && stack->array[i-2] == 'S') { // E->(E)
        pop(stack, 3);
        push(stack, 'S');
        action = 2;
    } else if (stack->array[i] == ')' && stack->array[i-1] == 'S' && stack->array[i-2] == '(') { // E->E*E
        pop(stack, 3);
        push(stack, 'S');
        action = 3;
    } else if (stack->array[i] == 'S' && stack->array[i-1] == '-' && stack->array[i-2] == 'S') { // E->E+E
        pop(stack, 3);
        push(stack, 'S');
        action = 4;
    } 
    return action; // 0 means cant reduce
}

int main() {
    struct Stack stack;
    stack.top = -1;
    push(&stack, '$');

    printf("GRAMMAR is\n Sr parser\n S->S+S\n S->S-S\n S->(S) \n S->a\n\nInput: ");
    char input[100];
    scanf("%s", input);
    printf("Stack\t\tInput\t\tAction\n");

    int inputLen = strlen(input);
    int i = 0;
    input[inputLen] = '$'; // Add $ at the end of string
    input[inputLen+1] = '\0';
    while (i < inputLen || stack.top != 1) {
        printf("\n");
        int reduceAction = reduce(&stack);

        if (reduceAction == 0) {
            if (i >= inputLen) { // Rejection condition (cant reduce and no more input)
                printf("\nRejected");
                return 0;
            }
            if (input[i] == 'i' && input[i + 1] == 'd') {
                push(&stack, 'i');
                print(&stack);
                printf("\t\t%s", &input[i]);
                printf("\t\tSHIFT->id");
                i++;
            } else {
                push(&stack, input[i]);
                print(&stack);
                printf("\t\t%s", &input[i]);
                printf("\t\tSHIFT->symbol");
            }            

            i++;
        } else if (reduceAction == 1){ // id-> id
            print(&stack);
            printf("\t\t%s ", &input[i]);
            printf("\t\tREDUCED id TO E");
        } else if (reduceAction == 2) { // E-> (E)
            print(&stack);
            printf("\t\t%s ", &input[i]);
            printf("\t\tREDUCED (E) TO E");
        } else if (reduceAction == 3) { // E-> E*E
            print(&stack);
            printf("\t\t%s ", &input[i]);
            printf("\t\tREDUCED E * E TO E");
        } else if (reduceAction == 4) { // E->E+E
            print(&stack);
            printf("\t\t%s ", &input[i]);
            printf("\t\tREDUCED E + E TO E");
        } else if (reduceAction == 5) { // E->E-E
            print(&stack);
            printf("\t\t%s ", &input[i]);
            printf("\t\tREDUCED E - E TO E");
        }
    }

    printf("\nAccepted");
    return 0;
}

