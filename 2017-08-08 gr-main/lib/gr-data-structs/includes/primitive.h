#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <stdbool.h>
#include <float.h>
#include <stdint.h>
#include <wchar.h>

/*******************************************************************************************/

// Data types.

union primitive_value {
    bool boolValue;
    int8_t byteValue;
    int16_t shortValue;
    int32_t intValue;
    int64_t longValue;

    uint8_t ubyteValue;
    uint16_t ushortValue;
    uint32_t uintValue;
    uint64_t ulongValue;

    float floatValue;
    double doubleValue;

    void *pointerValue;

    char charValue;
    wchar_t wcharValue;
    char *stringValue;
    wchar_t *wstringValue;
};

/*******************************************************************************************/

// Global variables.

extern union primitive_value primitive_null;

/*******************************************************************************************/

// Constructors.

extern union primitive_value primitive_getBool(bool boolValue);
extern union primitive_value primitive_getByte(int8_t byteValue);
extern union primitive_value primitive_getShort(int16_t shortValue);
extern union primitive_value primitive_getInt(int32_t intValue);
extern union primitive_value primitive_getLong(int64_t outLongValue);
extern union primitive_value primitive_getUByte(uint8_t ubyteValue);
extern union primitive_value primitive_getUShort(uint16_t ushortValue);
extern union primitive_value primitive_getUInt(uint32_t uintValue);
extern union primitive_value primitive_getULong(uint64_t ulongValue);
extern union primitive_value primitive_getFloat(float floatValue);
extern union primitive_value primitive_getDouble(double doubleValue);
extern union primitive_value primitive_getPointer(void *pointerValue);
extern union primitive_value primitive_getChar(char charValue);
extern union primitive_value primitive_getWChar(wchar_t wcharValue);
extern union primitive_value primitive_getString(char *stringValue);
extern union primitive_value primitive_getWString(wchar_t *wstringValue);

/*******************************************************************************************/

// Free.

extern void primitive_free(union primitive_value value);

/*******************************************************************************************/

// Compare values.

extern int32_t primitive_cmpBool(union primitive_value value1, union primitive_value value2);
extern int32_t primitive_cmpByte(union primitive_value value1, union primitive_value value2);
extern int32_t primitive_cmpShort(union primitive_value value1, union primitive_value value2);
extern int32_t primitive_cmpInt(union primitive_value value1, union primitive_value value2);
extern int32_t primitive_cmpLong(union primitive_value value1, union primitive_value value2);
extern int32_t primitive_cmpUByte(union primitive_value value1, union primitive_value value2);
extern int32_t primitive_cmpUShort(union primitive_value value1, union primitive_value value2);
extern int32_t primitive_cmpUInt(union primitive_value value1, union primitive_value value2);
extern int32_t primitive_cmpULong(union primitive_value value1, union primitive_value value2);
extern int32_t primitive_cmpFloat(union primitive_value value1, union primitive_value value2);
extern int32_t primitive_cmpDouble(union primitive_value value1, union primitive_value value2);
extern int32_t primitive_cmpPointer(union primitive_value value1, union primitive_value value2);
extern int32_t primitive_cmpChar(union primitive_value value1, union primitive_value value2);
extern int32_t primitive_cmpWChar(union primitive_value value1, union primitive_value value2);
extern int32_t primitive_cmpString(union primitive_value value1, union primitive_value value2);
extern int32_t primitive_cmpWString(union primitive_value value1, union primitive_value value2);

/*******************************************************************************************/

// Calculate hash code.

extern uint32_t primitive_hashRawUint(uint32_t u);
extern uint32_t primitive_hashRawULong(uint64_t u);
extern uint32_t primitive_hashRawDouble(double d);
extern uint32_t primitive_hashRawString(char *string);
extern uint32_t primitive_hashRawWString(wchar_t *wstring);
extern uint32_t primitive_hashBool(union primitive_value value);
extern uint32_t primitive_hashByte(union primitive_value value);
extern uint32_t primitive_hashShort(union primitive_value value);
extern uint32_t primitive_hashInt(union primitive_value value);
extern uint32_t primitive_hashLong(union primitive_value value);
extern uint32_t primitive_hashUByte(union primitive_value value);
extern uint32_t primitive_hashUShort(union primitive_value value);
extern uint32_t primitive_hashUInt(union primitive_value value);
extern uint32_t primitive_hashULong(union primitive_value value);
extern uint32_t primitive_hashFloat(union primitive_value value);
extern uint32_t primitive_hashDouble(union primitive_value value);
extern uint32_t primitive_hashPointer(union primitive_value value);
extern uint32_t primitive_hashChar(union primitive_value value);
extern uint32_t primitive_hashWChar(union primitive_value value);
extern uint32_t primitive_hashString(union primitive_value value);
extern uint32_t primitive_hashWString(union primitive_value value);

/*******************************************************************************************/

#endif /* PRIMITIVE_H */
