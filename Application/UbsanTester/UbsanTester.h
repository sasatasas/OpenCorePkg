#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>
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

#if defined (__clang__)

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

#endif
