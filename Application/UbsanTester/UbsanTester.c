#include "UbsanTester.h"

__attribute__ ((nonnull)) 
INT32
EFIAPI
F1 (
  INT32  *Nonnull,
  INT32  n
  )
{
  return *Nonnull;
}

__attribute__ ((nonnull)) 
CHAR8
EFIAPI
F2 (
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

__attribute__ ((returns_nonnull)) 
INT32 *
EFIAPI
F3 (
  INT32  *Nonnull
  )
{
  return Nonnull;
}

__attribute__ ((returns_nonnull)) 
INT32 *
EFIAPI
F4 (
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
F6 (
  INT32  n
  )
{
  n = __builtin_ctz (n);
  return 0;
}

INT64
EFIAPI
F7 (
  INT64  n
  )
{
  n = __builtin_ctzll (n);
  return 0;
}

INT32
EFIAPI
F8 (
  INT32  n
  )
{
  n = __builtin_clz (n);
  return 0;
}

INT64
EFIAPI
F9 (
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

INT32
EFIAPI
GetIntFromMultidemArr (
  INT32  i,
  INT32  j,
  INT32  k
  )
{
  INT32  arr[2][3][4] = { };

  return arr[i][j][k];
}

#ifdef TEST_BOUNDS
VOID
EFIAPI
BoundsCheck (
  VOID
  )
{
  INT32  Bar[2], i = 2, j = 3, k = 4;

  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with bounds...\n\n\n"));

  GetInt (Bar, i);
  DEBUG ((DEBUG_WARN, "UBT: Index 2 is out of range for type \'INT32 *\' (aka 'int *')\n\n"));
  GetIntFromMultidemArr (i, j - 1, k - 1);
  DEBUG ((DEBUG_WARN, "UBT: Index 2 is out of range for type \'INT32[2][3][4]\' (aka 'int[2][3][4]')\n\n"));
  GetIntFromMultidemArr (i - 1, j, k - 1);
  DEBUG ((DEBUG_WARN, "UBT: Index 3 is out of range for type \'INT32[3][4]\' (aka 'int[3][4]')\n\n"));
  GetIntFromMultidemArr (i - 1, j - 1, k);
  DEBUG ((DEBUG_WARN, "UBT: Index 4 is out of range for type \'INT32[4]\' (aka 'int[4]')\n\n"));

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

  F1 (p, 8);
  DEBUG ((DEBUG_WARN, "UBT: Null pointer passed as argument 1, which is declared to never be null\n\n"));
  DEBUG ((DEBUG_WARN, "UBT: Load of null pointer of type 'INT32' (aka 'int')\n\n"));
  F2 (8, p);
  DEBUG ((DEBUG_WARN, "UBT: Null pointer passed as argument 2, which is declared to never be null\n\n"));
  DEBUG ((DEBUG_WARN, "UBT: Load of null pointer of type 'CHAR8' (aka 'char')\n\n"));
  F3 (p);
  DEBUG ((DEBUG_WARN, "UBT: Null pointer returned from function declared to never return null\n\n"));
  F4 (p, 8);
  DEBUG ((DEBUG_WARN, "UBT: Null pointer returned from function declared to never return null\n\n"));
  F4 (p, -8);
  DEBUG ((DEBUG_WARN, "UBT: Null pointer returned from function declared to never return null\n\n"));

  NonnullReturn (NULL); // doesn't work
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
  F6 (0);
  DEBUG ((DEBUG_WARN, "UBT: Passing zero to ctz(), which is not a valid argument\n\n"));
  F7 (0); // in ubsan in llvm also not unique message for ctzll
  DEBUG ((DEBUG_WARN, "UBT: Passing zero to ctz(), which is not a valid argument\n\n"));
  F8 (0);
  DEBUG ((DEBUG_WARN, "UBT: Passing zero to clz(), which is not a valid argument\n\n"));
  F9 (0);
  DEBUG ((DEBUG_WARN, "UBT: Passing zero to clz(), which is not a valid argument\n\n"));

  DEBUG ((DEBUG_INFO, "\nUBT: Checks with builtin are done...\n\n\n\n\n"));
}

#endif

// #ifdef TEST_BOOLEAN
// BOOLEAN
// EFIAPI
// BooleanCheck (
//   VOID
//   )
// {
//   UINT8    NotABool = 123;
//   BOOLEAN  *P       = (BOOLEAN *)&NotABool;
//   BOOLEAN  B        = *P;
//   DEBUG ((DEBUG_INFO, "UBT: Start testing cases with boolean...\n\n\n"));
//   DEBUG ((DEBUG_WARN, "UBT: Load of value 123, which is not a valid value for type 'BOOLEAN'\n\n"));
//   DEBUG ((DEBUG_INFO, "\nUBT: Checks with boolean are done...\n\n\n\n\n"));

//   return B;
// }
// #endif

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  // TODO: delete me
  // Print (L"\nUBT: Trap mode %d, %d...\n\n", (INT32) UBSAN_ALWAYS_FATAL, (INT32) FixedPcdGetBool (PcdOcGuardUBSanTrapMode));
  // DEBUG ((DEBUG_INFO, "\nUBT: Trap mode %d, %d...\n\n", (INT32) UBSAN_ALWAYS_FATAL, (INT32) FixedPcdGetBool (PcdOcGuardUBSanTrapMode)));

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

  // #ifdef TEST_BOOLEAN
  //   BooleanCheck (); // TODO: doesn't work
  // #endif

 #ifdef TEST_IMPLICIT_CONVERSION
  CheckConvertArithmeticsValue ();
 #endif
  DEBUG ((DEBUG_INFO, "\nUBT: All tests are done...\n\n"));

  return EFI_SUCCESS;
}
