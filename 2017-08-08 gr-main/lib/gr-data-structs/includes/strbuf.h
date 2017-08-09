#ifndef STRBUF_H
#define STRBUF_H

#include <wchar.h>

/*******************************************************************************************/

// Constants.

#define STRBUF_DEFAULT_INITIAL_CAPACITY             4

/*******************************************************************************************/

// Data types.

struct strbuf {
    uint32_t size;
    uint32_t capacity;
    char *string;
};

/*******************************************************************************************/

// Utils.

extern char *string_dup(const char *s);

/*******************************************************************************************/

// Constructors.

extern struct strbuf *strbuf_create(void);
extern struct strbuf *strbuf_create1(uint32_t initialCapacity);

/*******************************************************************************************/

// Basic operations.

extern void strbuf_puts(struct strbuf *buf, char *s);
extern void strbuf_putc(struct strbuf *buf, char c);
extern char strbuf_get(struct strbuf *buf, uint32_t index);
extern void strbuf_set(struct strbuf *buf, uint32_t index, char c);
extern void strbuf_clear(struct strbuf *buf);

/*******************************************************************************************/

// Destructor.

extern void strbuf_free(struct strbuf *buf);

/*******************************************************************************************/

#endif /* STRBUF_H */
