#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

#define UINT64_MAX  ((UINT64)0xFFFFFFFFFFFFFFFFULL)
#define UINT32_MAX  ((UINT32)0xFFFFFFFF)
#define UINT16_MAX  ((UINT16)0xFFFF)
#define UINT8_MAX   ((UINT8)0xFF)

#define INT64_MIN  ((INT64)0xFFFFFFFFFFFFFFFFULL)
#define INT32_MIN  ((INT32)0xFFFFFFFF)
#define INT16_MIN  ((INT16)0xFFFF)
#define INT8_MIN   ((INT8)0xFF)

#define INT32_MAX  ((INT32)0x7FFFFFFF)
#define INT8_MAX   ((INT8)0x7F)

/* Implicit conversion group of checks. */
VOID
CheckConvertArithmeticsValue (
  VOID
  );

/* Pointer overflow. */
VOID
PointerCheck (
  VOID
  );

/* Alignment. */
VOID
AlignmentCheck (
  VOID
  );

// Avoid implementing memcpy as a function to avoid LTO conflicts.
#define memcpy(Dst, Src, Size)  do { gBS->CopyMem(Dst, Src, Size); } while (0)
