/*
 * =============================================================================
 * common.h - Shared data types for Chimera OS
 * =============================================================================
 * Provides a central place for common type definitions (typedefs) to ensure
 * consistency across the kernel components.
 * =============================================================================
 */

#ifndef COMMON_H
#define COMMON_H

// Standard integer types
typedef unsigned int   u32int;
_Static_assert(sizeof(u32int) == 4, "u32int must be 4 bytes");
typedef          int   s32int;
_Static_assert(sizeof(s32int) == 4, "s32int must be 4 bytes");
typedef unsigned short u16int;
_Static_assert(sizeof(u16int) == 2, "u16int must be 2 bytes");
typedef          short s16int;
_Static_assert(sizeof(s16int) == 2, "s16int must be 2 bytes");
typedef unsigned char  u8int;
_Static_assert(sizeof(u8int) == 1, "u8int must be 1 byte");
typedef          char  s8int;
_Static_assert(sizeof(s8int) == 1, "s8int must be 1 byte");

#endif // COMMON_H
