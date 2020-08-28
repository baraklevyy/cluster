#include <stdio.h>
#include <stdlib.h>
#include "Common.h"
#include "Stack.h"

int isEmpty(const struct _Stack *s) {
    return ((s->size == 0) ? 1 : 0);
}

Dick* stack_pop(struct _Stack *s) {
    Status status = INVALID_STATUS_CODE;
    Dick *d;
    if (s->size == 0) {
        status = NULL_ARGUMENT_CODE;
        get_error_message(status);
        exit(status);
    }
    d = s->head;
    s->head = s->head->previous;
    s->size -= 1;
    return d;

}

void stack_push(struct _Stack *s, struct _Dicks *d) {
    Dick *tmp = NULL;
    /*
    if (!(s->is_empty(s))) {
        Dick *tmp = s->head;
    }
    s->head->previous = d;
    s->head = d;
    d->previous = tmp;
    s->size += 1;
    */
    if (s->size == 0){
        s->head = d;
    }
    else {
        tmp = s->head;
        s->head = d;
        s->head->previous = tmp;
    }
    s->size += 1;

}

Stack* stack_allocate() {
    Status status = INVALID_STATUS_CODE;
    Stack *s = NULL;

    /*Initializing functions pointers*/
    Dick*(*pop_ptr)(struct _Stack *);
    void(*push_ptr)(struct _Stack *, struct _Dicks *);
    pop_ptr = &(stack_pop);
    push_ptr = &(stack_push);
    /*Allocating Stack*/
    s = (Stack*)malloc(sizeof(Stack));
    if (NULL == s) {
        status = MALLOC_FAILED_CODE;
        get_error_message(status);
        goto l_cleanup;
    }
    /*Initiazling Stack members*/
    s->size = 0;
    s->pop = pop_ptr;
    s->push = push_ptr;

    status = SUCCESS_STATUS_CODE;
    return s;
    l_cleanup:
    exit(status);
}



