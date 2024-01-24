#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <../../Library/OcGuardLib/Ubsan.h>

#define CHECK_GROUP FixedPcdGet8 (PcdOcGuardUBSanCheckGroup)
#if (CHECK_GROUP & (1U << 0))
  #define TEST_UNDEFINED
#endif
#if (FixedPcdGet8 (PcdOcGuardUBSanCheckGroup) & (1U << 1))
  #define TEST_ALIGNMENT
#endif
#if (FixedPcdGet8 (PcdOcGuardUBSanCheckGroup) & (1U << 2))
  #define TEST_BUILTIN
#endif
#if (FixedPcdGet8 (PcdOcGuardUBSanCheckGroup) & (1U << 3))
  #define TEST_BOUNDS
#endif
#if (FixedPcdGet8 (PcdOcGuardUBSanCheckGroup) & (1U << 4))
  #define TEST_IMPLICIT_CONVERSION
#endif
#if (FixedPcdGet8 (PcdOcGuardUBSanCheckGroup) & (1U << 5))
  #define TEST_INTEGER
#endif
#if (FixedPcdGet8 (PcdOcGuardUBSanCheckGroup) & (1U << 6))
  #define TEST_NONNULL
#endif
#if (FixedPcdGet8 (PcdOcGuardUBSanCheckGroup) & (1U << 7))
  #define TEST_POINTER
#endif

#ifdef TEST_UNDEFINED
#define TEST_ALIGNMENT
#define TEST_NONNULL
#define TEST_BOUNDS // -fsanitize=local-bounds also include
#define TEST_POINTER
#define TEST_BUILTIN
#define TEST_BOOLEAN
#endif

#define INT64_MIN  ((INT64)0xFFFFFFFFFFFFFFFFULL)
#define INT32_MIN  ((INT32)0xFFFFFFFF)
#define INT16_MIN  ((INT16)0xFFFF)
#define INT8_MIN   ((INT8)0xFF)

#define INT32_MAX  ((INT32)0x7FFFFFFF)
#define INT8_MAX   ((INT8)0x7F)

/* Implicit conversion group of checks. */
VOID
EFIAPI
CheckConvertArithmeticsValue (
  VOID
  );

/* Pointer overflow. */
VOID
EFIAPI
PointerCheck (
  VOID
  );

/* Alignment. */
VOID
EFIAPI
AlignmentCheck (
  VOID
  );