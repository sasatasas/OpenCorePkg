#include "UbsanTester.h"

__attribute__ ((nonnull)) INT32
EFIAPI
Nonnull1 (
  INT32  *Nonnull,
  INT32  N
  )
{
  return *Nonnull;
}

__attribute__ ((nonnull)) CHAR8
EFIAPI
Nonnull2 (
  INT32  N,
  ...
  )
{
  VA_LIST  Args;

  VA_START (Args, N);

  CHAR8  *Nonnull = VA_ARG (Args, CHAR8 *);
  CHAR8  Res      = *Nonnull;

  VA_END (Args);
  return Res;
}

__attribute__ ((returns_nonnull)) INT32 *
EFIAPI
Nonnull3 (
  INT32  *Nonnull
  )
{
  return Nonnull;
}

__attribute__ ((returns_nonnull)) INT32 *
EFIAPI
Nonnull4 (
  INT32  *Nonnull,
  INT32  N
  )
{
  if (N > 0) {
    return Nonnull;
  } else {
    return Nonnull;
  }
}

INT32 *_Nonnull
EFIAPI
NonnullReturn (
  INT32  *P
  )
{
  return P;
}

VOID
EFIAPI
NonnullArg (
  INT32 *_Nonnull  P
  )
{
}

INT32
EFIAPI
Bultin1 (
  INT32  N
  )
{
  N = __builtin_ctz (N);
  return 0;
}

INT64
EFIAPI
Bultin2 (
  INT64  N
  )
{
  N = __builtin_ctzll (N);
  return 0;
}

INT32
EFIAPI
Bultin3 (
  INT32  N
  )
{
  N = __builtin_clz (N);
  return 0;
}

INT64
EFIAPI
Bultin4 (
  INT64  N
  )
{
  N = __builtin_clzll (N);
  return 0;
}

INT32
EFIAPI
GetInt (
  INT32 *CONST  P __attribute__ ((pass_object_size (0))),
  INT32         I
  )
{
  return P[I];
}

#ifdef TEST_BOUNDS
VOID
EFIAPI
BoundsCheck (
  VOID
  )
{
  INT32  Bar[2], I = 2;

  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with bounds...\n\n"));
  GetInt (Bar, I);
  DEBUG ((DEBUG_WARN, "\nUBT: Index 2 is out of range for type \'INT32 *\' (aka 'int *')\n"));
  DEBUG ((DEBUG_INFO, "\n\nUBT: Checks with bounds are done...\n\n\n"));
}

#endif

#ifdef TEST_NONNULL
VOID
EFIAPI
NonnullCheck (
  VOID
  )
{
  INT32  *P = 0;

  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with nonnull atribute...\n\n"));

  Nonnull1 (P, 8);
  DEBUG ((DEBUG_WARN, "\nUBT: Null pointer passed as argument 1, which is declared to never be null\n"));
  Nonnull2 (8, P);
  DEBUG ((DEBUG_WARN, "\nUBT: Null pointer passed as argument 2, which is declared to never be null\n"));
  Nonnull3 (P);
  DEBUG ((DEBUG_WARN, "\nUBT: Null pointer returned from function declared to never return null\n"));
  Nonnull4 (P, 8);
  DEBUG ((DEBUG_WARN, "\nUBT: Null pointer returned from function declared to never return null\n"));
  Nonnull4 (P, -8);
  DEBUG ((DEBUG_WARN, "\nUBT: Null pointer returned from function declared to never return null\n"));

  NonnullReturn (NULL);
  DEBUG ((DEBUG_WARN, "\nUBT: Null pointer returned from function declared to never return null\n"));
  NonnullArg (P);
  DEBUG ((DEBUG_WARN, "\nUBT: Null pointer passed as argument 1, which is declared to never be null\n"));

  DEBUG ((DEBUG_INFO, "\n\nUBT: Checks with nonnull atribute are done...\n\n\n"));
}

#endif

#ifdef TEST_BUILTIN
VOID
EFIAPI
BuiltinCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with builtin...\n\n"));
  Bultin1 (0);
  DEBUG ((DEBUG_WARN, "\nUBT: Passing zero to ctz(), which is not a valid argument\n"));
  Bultin2 (0); // in ubsan in llvm also not unique message for ctzll
  DEBUG ((DEBUG_WARN, "\nUBT: Passing zero to ctz(), which is not a valid argument\n"));
  Bultin3 (0);
  DEBUG ((DEBUG_WARN, "\nUBT: Passing zero to clz(), which is not a valid argument\n"));
  Bultin4 (0);
  DEBUG ((DEBUG_WARN, "\nUBT: Passing zero to clz(), which is not a valid argument\n"));

  DEBUG ((DEBUG_INFO, "\n\nUBT: Checks with builtin are done...\n\n\n"));
}

#endif

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
 #ifdef TEST_ALIGNMENT
  AlignmentCheck ();
 #endif
 #ifdef TEST_NONNULL
  NonnullCheck ();
 #endif
 #ifdef TEST_BOUNDS
  BoundsCheck ();
 #endif
 #ifdef TEST_POINTER
  PointerCheck ();
 #endif
 #ifdef TEST_BUILTIN
  BuiltinCheck ();
 #endif
 #ifdef TEST_IMPLICIT_CONVERSION
  ImplicitConversionCheck ();
 #endif
 #ifdef TEST_INTEGER
  IntegerCheck ();
 #endif
  DEBUG ((DEBUG_INFO, "\n\nUBT: All tests are done...\n"));

  return EFI_SUCCESS;
}
