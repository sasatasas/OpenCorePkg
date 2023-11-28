#include "UbsanTester.h"

__attribute__ ((nonnull)) INT32
EFIAPI
F1 (
  INT32  *Nonnull,
  INT32  n
  )
{
  return *Nonnull;
}

__attribute__ ((nonnull)) CHAR8
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

__attribute__ ((returns_nonnull)) INT32 *
EFIAPI
F3 (
  INT32  *Nonnull
  )
{
  return Nonnull;
}

__attribute__ ((returns_nonnull)) INT32 *
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

VOID
EFIAPI
BoundsCheck (
  VOID
  )
{
  INT32  Bar[2], i = 2, j = 3, k = 4;

  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with bounds...\n\n\n"));

  GetInt (Bar, i);
  DEBUG ((DEBUG_WARN, "UBT: Index 2 out of bounds for type \'INT32 *\'...\n\n"));
  GetIntFromMultidemArr (i, j - 1, k - 1);
  DEBUG ((DEBUG_WARN, "UBT: Index 2 out of bounds for type \'INT32[2][3][4]\'...\n\n"));
  GetIntFromMultidemArr (i - 1, j, k - 1);
  DEBUG ((DEBUG_WARN, "UBT: Index 2 out of bounds for type \'INT32[3][4]\'...\n\n"));
  GetIntFromMultidemArr (i - 1, j - 1, k);
  DEBUG ((DEBUG_WARN, "UBT: Index 2 out of bounds for type \'INT32[4]\'...\n\n"));

  DEBUG ((DEBUG_INFO, "\nUBT: Checks with bounds are done...\n\n\n\n\n"));
}

VOID
EFIAPI
NonnullCheck (
  VOID
  )
{
  INT32  *p = 0;

  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with nonnull atribute...\n\n\n"));

  F1 (p, 8);
  DEBUG ((DEBUG_WARN, "UBT: Null pointer passed as argument 1, which is declared to never be null...\n\n"));
  F2 (8, p);
  DEBUG ((DEBUG_WARN, "UBT: Null pointer passed as argument 2, which is declared to never be null...\n\n"));
  F3 (p);
  DEBUG ((DEBUG_WARN, "UBT: Null pointer returned from function declared to never return null...\n\n"));
  F4 (p, 8);
  DEBUG ((DEBUG_WARN, "UBT: Null pointer returned from function declared to never return null...\n\n"));
  F4 (p, -8);
  DEBUG ((DEBUG_WARN, "UBT: Null pointer returned from function declared to never return null...\n\n"));

  NonnullReturn (NULL); // doesn't work
  DEBUG ((DEBUG_WARN, "UBT: Null pointer returned from function declared to never return null... (_Nonnull)\n\n"));
  NonnullArg (p);
  DEBUG ((DEBUG_WARN, "UBT: Null pointer passed as argument 1, which is declared to never be null... (_Nonnull)\n\n"));

  DEBUG ((DEBUG_INFO, "\nUBT: Checks with nonnull atribute are done...\n\n\n\n\n"));
}

VOID
EFIAPI
ShiftOutOfBoundsCheck (
  VOID
  )
{
  UINT16  p = 1;

  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with shift out of bounds...\n\n\n"));

  INT32  i = 32;

  p >>= i;
  DEBUG ((DEBUG_WARN, "UBT: Shift exponent 32 is too large for 16-bit type\n\n"));

  p   = 1;
  i   = -1;
  p >>= i;
  DEBUG ((DEBUG_WARN, "UBT: Shift exponent -1 is negative\n\n"));

  p   = 1;
  i   = 32;
  p <<= i;
  DEBUG ((DEBUG_WARN, "UBT: Shift exponent 32 is too large for 16-bit type\n\n"));

  p   = 1;
  i   = -1;
  p <<= i;
  DEBUG ((DEBUG_WARN, "UBT: Shift exponent -1 is negative\n\n"));

  i = 31;
  i = 1 << i;
  DEBUG ((DEBUG_WARN, "UBT: Left shift of 1 by 31 places cannot be represented in 32-bit type \n\n"));

  INT32  q = -1;

  i   = 5;
  q <<= i;
  DEBUG ((DEBUG_WARN, "UBT: Left shift of negative value -1\n\n"));

  DEBUG ((DEBUG_INFO, "\nUBT: Checks with shift out of bounds are done...\n\n\n\n\n"));
}

VOID
EFIAPI
BuiltinCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with builtin...\n\n\n"));
  F6 (0);
  DEBUG ((DEBUG_WARN, "UBT: Passing zero to ctz(), which is not a valid argument\n\n"));
  F7 (0);
  DEBUG ((DEBUG_WARN, "UBT: Passing zero to ctzll(), which is not a valid argument\n\n"));
  F8 (0);
  DEBUG ((DEBUG_WARN, "UBT: Passing zero to clz(), which is not a valid argument\n\n"));
  F9 (0);
  DEBUG ((DEBUG_WARN, "UBT: Passing zero to clzll(), which is not a valid argument\n\n"));

  DEBUG ((DEBUG_INFO, "\nUBT: Checks with builtin are done...\n\n\n\n\n"));
}

BOOLEAN
EFIAPI
BooleanCheck (
  VOID
  )
{
  UINT8    NotABool = 123;
  BOOLEAN  *P       = (BOOLEAN *)&NotABool;
  BOOLEAN  B        = *P;

  DEBUG ((DEBUG_WARN, "UBT: Load of value 123, which is not a valid value for type 'BOOLEAN'\n\n"));

  return B;
}

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  AlignmentCheck ();
  NonnullCheck ();
  ShiftOutOfBoundsCheck ();
  BoundsCheck ();
  PointerCheck ();
  BuiltinCheck ();
  BooleanCheck (); // TODO: doesn't work

  /*
    Implicit conversion + Integer
    Doesnt work with the tests above
  */
  // CheckConvertArithmeticsValue ();

  DEBUG ((DEBUG_INFO, "\nUBT: All tests are done...\n\n"));
  CpuDeadLoop ();

  return EFI_SUCCESS; ///< Unreachable
}
