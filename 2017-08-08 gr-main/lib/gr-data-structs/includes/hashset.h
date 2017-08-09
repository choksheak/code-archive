#ifndef HASHSET_H
#define HASHSET_H

#include "iterator.h"

/*******************************************************************************************/

// Data types.

// For use in the constructor, like in the Builder pattern.
// Only keyType is required. The rest are optional.
struct hashset_config {
    uint32_t initialCapacity;
    uint32_t loadFactorOverThousand;
    uint32_t (*hashFunc)(union primitive_value);
    int32_t (*cmpFunc)(union primitive_value, union primitive_value);
};

struct hashset {
    struct hashmap *map;
    uint32_t size;
};

/*******************************************************************************************/

// Constructors.

extern struct hashset *hashset_createByteSet();
extern struct hashset *hashset_createShortSet();
extern struct hashset *hashset_createIntSet();
extern struct hashset *hashset_createLongSet();
extern struct hashset *hashset_createUByteSet();
extern struct hashset *hashset_createUShortSet();
extern struct hashset *hashset_createUIntSet();
extern struct hashset *hashset_createULongSet();
extern struct hashset *hashset_createFloatSet();
extern struct hashset *hashset_createDoubleSet();
extern struct hashset *hashset_createPointerSet();
extern struct hashset *hashset_createCharSet();
extern struct hashset *hashset_createWCharSet();
extern struct hashset *hashset_createStringSet();
extern struct hashset *hashset_createWStringSet();
extern struct hashset *hashset_create(struct hashset_config config);

/*******************************************************************************************/

// Basic operations.

extern bool hashset_put(struct hashset *set, union primitive_value value);
extern bool hashset_contains(struct hashset *set, union primitive_value value);
extern bool hashset_remove(struct hashset *set, union primitive_value value);
extern void hashset_clear(struct hashset *set);

/*******************************************************************************************/

// Iterators.

extern struct iterator hashset_iterator(struct hashset *set);
extern bool hashset_next(struct iterator *iterator, struct iterator_return *returnValue);
extern void hashset_rewind(struct iterator *iterator);

/*******************************************************************************************/

// Destructor.

extern void hashset_free(struct hashset *set);

/*******************************************************************************************/

#endif /* HASHSET_H */
