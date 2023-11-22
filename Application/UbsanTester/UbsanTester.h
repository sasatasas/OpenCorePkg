#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <limits.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>

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
