#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>

/* Implicit conversion group of checks. */
void
CheckConvertArithmeticsValue (
  VOID
  );

// TODO: __ubsan_handle_alignment_assumption hasn't yet been implemented
/* Pointer overflow. */
void
PointerCheck (
  VOID
  );
