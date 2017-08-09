#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdbool.h>

#include "primitive.h"

// This struct simplifies iterator return values, because we will not likely need to
// return more than two values for any kind of iteration.
struct iterator_return {
    union primitive_value key;
    union primitive_value value;
};

// An iterator strictly never allocates any memory, and thus no memory needs to be freed.
struct iterator {
    bool (*nextFunc)(struct iterator *, struct iterator_return *);
    void (*rewindFunc)(struct iterator *);

    // Generic storage for internal iterator implementations.
    union primitive_value iteratorInternal1;
    union primitive_value iteratorInternal2;
    union primitive_value iteratorInternal3;
};

extern void iterator_each(struct iterator *iterator, void (*func)(struct iterator_return));

#endif /* ITERATOR_H */
