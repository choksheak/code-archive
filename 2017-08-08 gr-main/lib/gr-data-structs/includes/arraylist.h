#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "iterator.h"

/*******************************************************************************************/

// Constants.

#define ARRAYLIST_DEFAULT_INITIAL_CAPACITY          4

/*******************************************************************************************/

// Data types.

struct arraylist {
    uint32_t size;
    uint32_t capacity;
    union primitive_value *values;
};

/*******************************************************************************************/

// Constructors.

extern struct arraylist *arraylist_create(void);
extern struct arraylist *arraylist_create1(uint32_t initialCapacity);

/*******************************************************************************************/

// Basic operations.

extern void arraylist_add(struct arraylist *list, union primitive_value value);
extern union primitive_value arraylist_get(struct arraylist *list, uint32_t index);
extern void arraylist_set(struct arraylist *list, uint32_t index, union primitive_value value);
extern union primitive_value arraylist_remove(struct arraylist *list, uint32_t index);
extern void arraylist_clear(struct arraylist *list);

/*******************************************************************************************/

// More operations.

extern void arraylist_removeRange(struct arraylist *list, uint32_t fromIndexInclusive, uint32_t toIndexExclusive);

/*******************************************************************************************/

// Iterators.

extern struct iterator arraylist_iterator(struct arraylist *list);
extern bool arraylist_next(struct iterator *iterator, struct iterator_return *returnValue);
extern void arraylist_rewind(struct iterator *iterator);

/*******************************************************************************************/

// Destructor.

extern void arraylist_free(struct arraylist *list);

/*******************************************************************************************/

#endif /* ARRAYLIST_H */
