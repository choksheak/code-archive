#ifndef HASHMAP_H
#define HASHMAP_H

#include "iterator.h"

/*******************************************************************************************/

// Constants.

#define HASHMAP_DEFAULT_INITIAL_CAPACITY            4
#define HASHMAP_DEFAULT_LOAD_FACTOR_OVER_THOUSAND   600
#define HASHMAP_MIN_LOAD_FACTOR_OVER_THOUSAND       100
#define HASHMAP_MAX_LOAD_FACTOR_OVER_THOUSAND       1000

/*******************************************************************************************/

// Data types.

struct hashmap_bucket {
    union primitive_value key;
    union primitive_value value;
    uint32_t hashCode;
    struct hashmap_bucket *next;
};

// For use in the constructor, like in the Builder pattern.
// Only keyType is required. The rest are optional.
struct hashmap_config {
    uint32_t initialCapacity;
    uint32_t loadFactorOverThousand;
    uint32_t (*hashFunc)(union primitive_value);
    int32_t (*cmpFunc)(union primitive_value, union primitive_value);
};

struct hashmap {
    // Config.
    uint32_t capacity;
    uint32_t loadFactorOverThousand;
    uint32_t (*hashFunc)(union primitive_value);
    int32_t (*cmpFunc)(union primitive_value, union primitive_value);

    // Other data.
    uint32_t size;
    struct hashmap_bucket **table;
};

/*******************************************************************************************/

// Constructors.

extern struct hashmap *hashmap_createByteMap();
extern struct hashmap *hashmap_createShortMap();
extern struct hashmap *hashmap_createIntMap();
extern struct hashmap *hashmap_createLongMap();
extern struct hashmap *hashmap_createUByteMap();
extern struct hashmap *hashmap_createUShortMap();
extern struct hashmap *hashmap_createUIntMap();
extern struct hashmap *hashmap_createULongMap();
extern struct hashmap *hashmap_createFloatMap();
extern struct hashmap *hashmap_createDoubleMap();
extern struct hashmap *hashmap_createPointerMap();
extern struct hashmap *hashmap_createCharMap();
extern struct hashmap *hashmap_createWCharMap();
extern struct hashmap *hashmap_createStringMap();
extern struct hashmap *hashmap_createWStringMap();
extern struct hashmap *hashmap_create(struct hashmap_config config);

/*******************************************************************************************/

// Basic operations.

extern bool hashmap_put(struct hashmap *map, union primitive_value key, union primitive_value value);
extern union primitive_value *hashmap_get(struct hashmap *map, union primitive_value key);
extern union primitive_value hashmap_getOrDefault(struct hashmap *map, union primitive_value key, union primitive_value defaultValue);
extern bool hashmap_containsKey(struct hashmap *map, union primitive_value key);
extern bool hashmap_remove(struct hashmap *map, union primitive_value key);
extern bool hashmap_getAndRemove(struct hashmap *map, union primitive_value key, struct iterator_return *removedEntry);
extern void hashmap_clear(struct hashmap *map);

/*******************************************************************************************/

// Iterators.

extern struct iterator hashmap_iterator(struct hashmap *map);
extern bool hashmap_next(struct iterator *iterator, struct iterator_return *returnValue);
extern void hashmap_rewind(struct iterator *iterator);

/*******************************************************************************************/

// Destructor.

extern void hashmap_free(struct hashmap *map);

/*******************************************************************************************/

#endif /* HASHMAP_H */
