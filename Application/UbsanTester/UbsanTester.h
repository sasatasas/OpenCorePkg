#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <../../Library/OcGuardLib/Ubsan.h>

#define UNDEFINED_TESTS_BIT            (1U << 0)
#define ALIGNMENT_TESTS_BIT            (1U << 1)
#define BUILTIN_TESTS_BIT              (1U << 2)
#define BOUNDS_TESTS_BIT               (1U << 3)
#define IMPLICIT_CONVERSION_TESTS_BIT  (1U << 4)
#define INTEGER_TESTS_BIT              (1U << 5)
#define NONNULL_TESTS_BIT              (1U << 6)
#define POINTER_TESTS_BIT              (1U << 7)

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
