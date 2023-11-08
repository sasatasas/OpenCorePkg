#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>

#define UINT64_MAX 0xFFFFFFFFFFFFFFFF
#define UINT32_MAX 0xFFFFFFFF
#define UINT16_MAX 0xFFFF
#define UINT8_MAX 0xFF

#define INT32_MAX (INT32)0x7FFFFFFF
#define INT8_MAX (INT8)0x7F

#define INT64_MIN (INT64)0xFFFFFFFFFFFFFFFF
#define INT32_MIN (INT32)0xFFFFFFFF
#define INT16_MIN (INT16)0xFFFF
#define INT8_MIN (INT8)0xFFa

// Implicit conversion group of checks.
void check_convert_arithmetics_value();

// __ubsan_handle_alignment_assumption hasn't yet been implemented
// Pointer overflow
void pointer_check();