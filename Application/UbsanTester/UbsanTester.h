#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <../../Library/OcGuardLib/Ubsan.h>

#define CHECK_GROUP  FixedPcdGet8 (PcdOcGuardUBSanCheckGroup)
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
#endif

#define INT64_MIN  ((INT64)0x8000000000000000ULL)
#define INT32_MIN  ((INT32)0x80000000)
#define INT16_MIN  ((INT16)0x8000)
#define INT8_MIN   ((INT8)0x80)

#define INT32_MAX  ((INT32)0x7FFFFFFF)
#define INT8_MAX   ((INT8)0x7F)

/*
 * Implicit conversion check group.
 *
 * -fsanitize=implicit-conversion
 *
 * Checks for suspicious behavior of implicit conversions.
 */
VOID
EFIAPI
ImplicitConversionCheck (
  VOID
  );

/*
 * Integer check groups.
 *
 * -fsanitize=integer
 *
 * Checks for undefined or suspicious integer behavior.
 */
VOID
EFIAPI
IntegerCheck (
  VOID
  );

/*
 * Pointer check groups.
 *
 * -fsanitize=pointer-overflow,null
 *
 * Use of a null pointer or creation of a null reference.
 * Performing pointer arithmetic which overflows, or where either
 * the old or/and new pointer value is a null pointer.
 */
VOID
EFIAPI
PointerCheck (
  VOID
  );

/*
 * Alignment check group.
 *
 * -fsanitize=alignment
 *
 * Use of a misaligned pointer or creation of a misaligned reference.
 */
VOID
EFIAPI
AlignmentCheck (
  VOID
  );
