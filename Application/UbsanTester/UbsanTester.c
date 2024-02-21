#include "UbsanTester.h"

__attribute__ ((nonnull)) INT32
EFIAPI
Nonnull1 (
  INT32  *Nonnull,
  INT32  n
  )
{
  return *Nonnull;
}

__attribute__ ((nonnull)) CHAR8
EFIAPI
Nonnull2 (
  INT32  n,
  ...
  )
{
  VA_LIST  Args;

  VA_START (Args, n);

  CHAR8  *Nonnull = VA_ARG (Args, CHAR8 *);
  CHAR8  res      = *Nonnull;

  VA_END (Args);
  return res;
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
  INT32  n
  )
{
  if (n > 0) {
    return Nonnull;
  } else {
    return Nonnull;
  }
}

INT32 *_Nonnull
EFIAPI
NonnullReturn (
  INT32  *p
  )
{
  return p;
}

VOID
EFIAPI
NonnullArg (
  INT32 *_Nonnull  p
  )
{
}

INT32
EFIAPI
Bultin1 (
  INT32  n
  )
{
  n = __builtin_ctz (n);
  return 0;
}

INT64
EFIAPI
Bultin2 (
  INT64  n
  )
{
  n = __builtin_ctzll (n);
  return 0;
}

INT32
EFIAPI
Bultin3 (
  INT32  n
  )
{
  n = __builtin_clz (n);
  return 0;
}

INT64
EFIAPI
Bultin4 (
  INT64  n
  )
{
  n = __builtin_clzll (n);
  return 0;
}

INT32
EFIAPI
GetInt (
  INT32 *CONST  p __attribute__ ((pass_object_size (0))),
  INT32         i
  )
{
  return p[i];
}

#ifdef TEST_BOUNDS
VOID
EFIAPI
BoundsCheck (
  VOID
  )
{
  INT32  Bar[2], i = 2;

  // INT32  Arr[2][3][4] = { };
  // INT32  Res, j = 3, k = 4;

  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with bounds...\n\n\n"));

  GetInt (Bar, i);
  DEBUG ((DEBUG_WARN, "UBT: Index 2 is out of range for type \'INT32 *\' (aka 'int *')\n\n"));
  // // Res = Arr[i][j - 1][k - 1];
  // // DEBUG ((DEBUG_WARN, "UBT: Index 2 is out of range for type \'INT32[2][3][4]\' (aka 'int[2][3][4]')\n\n"));
  // // Res = Arr[i - 1][j][k - 1];
  // // DEBUG ((DEBUG_WARN, "UBT: Index 3 is out of range for type \'INT32[3][4]\' (aka 'int[3][4]')\n\n"));
  // Res = Arr[i - 1][j - 1][k];
  // DEBUG ((DEBUG_WARN, "UBT: Index 4 is out of range for type \'INT32[4]\' (aka 'int[4]')\n\n"));

  DEBUG ((DEBUG_INFO, "\nUBT: Checks with bounds are done...\n\n\n\n\n"));
}

#endif

#ifdef TEST_NONNULL
VOID
EFIAPI
NonnullCheck (
  VOID
  )
{
  INT32  *p = 0;

  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with nonnull atribute...\n\n\n"));

  Nonnull1 (p, 8);
  DEBUG ((DEBUG_WARN, "UBT: Null pointer passed as argument 1, which is declared to never be null\n\n"));
  DEBUG ((DEBUG_WARN, "UBT: Load of null pointer of type 'INT32' (aka 'int')\n\n"));
  Nonnull2 (8, p);
  DEBUG ((DEBUG_WARN, "UBT: Null pointer passed as argument 2, which is declared to never be null\n\n"));
  DEBUG ((DEBUG_WARN, "UBT: Load of null pointer of type 'CHAR8' (aka 'char')\n\n"));
  Nonnull3 (p);
  DEBUG ((DEBUG_WARN, "UBT: Null pointer returned from function declared to never return null\n\n"));
  Nonnull4 (p, 8);
  DEBUG ((DEBUG_WARN, "UBT: Null pointer returned from function declared to never return null\n\n"));
  Nonnull4 (p, -8);
  DEBUG ((DEBUG_WARN, "UBT: Null pointer returned from function declared to never return null\n\n"));

  NonnullReturn (NULL);
  DEBUG ((DEBUG_WARN, "UBT: Null pointer returned from function declared to never return null\n\n"));
  NonnullArg (p);
  DEBUG ((DEBUG_WARN, "UBT: Null pointer passed as argument 1, which is declared to never be null\n\n"));

  DEBUG ((DEBUG_INFO, "\nUBT: Checks with nonnull atribute are done...\n\n\n\n\n"));
}

#endif

#ifdef TEST_BUILTIN
VOID
EFIAPI
BuiltinCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with builtin...\n\n\n"));
  Bultin1 (0);
  DEBUG ((DEBUG_WARN, "UBT: Passing zero to ctz(), which is not a valid argument\n\n"));
  Bultin2 (0); // in ubsan in llvm also not unique message for ctzll
  DEBUG ((DEBUG_WARN, "UBT: Passing zero to ctz(), which is not a valid argument\n\n"));
  Bultin3 (0);
  DEBUG ((DEBUG_WARN, "UBT: Passing zero to clz(), which is not a valid argument\n\n"));
  Bultin4 (0);
  DEBUG ((DEBUG_WARN, "UBT: Passing zero to clz(), which is not a valid argument\n\n"));

  DEBUG ((DEBUG_INFO, "\nUBT: Checks with builtin are done...\n\n\n\n\n"));
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
  DEBUG ((DEBUG_INFO, "\nUBT: All tests are done...\n\n"));

  return EFI_SUCCESS;
}
