#include "UbsanTester.h"

/*
  INT32 __attribute__ ((noinline))
  f1 (
    VOID
    )
  {
  }

  INT32
  missingReturn (
    VOID
    )
  {
    DEBUG ((DEBUG_INFO, "UBT: Start testing cases with missing
      value-returning..."));
    return f (VOID);
    DEBUG ((DEBUG_INFO, "UBT: DONE..."));
  }
*/

__attribute__ ((nonnull)) INT32
f1 (
  INT32  *nonnull,
  INT32  n
  )
{
  return *nonnull;
}
//
// __attribute__ ((nonnull)) CHAR8
// f2 (
//   INT32        n,
//   ...
//   )
// {
//   VA_LIST  Args;
//   VA_START (Args, n);

//   CHAR8  *nonnull = VA_ARG (Args, CHAR8 *);
//   CHAR8  res      = *nonnull;

//   VA_END (Args);
//   return res;
// }
//
__attribute__ ((returns_nonnull)) INT32 *
f3 (
  INT32  *nonnull
  )
{
  return nonnull;
}

__attribute__ ((returns_nonnull)) INT32 *
f4 (
  INT32  *nonnull,
  INT32  n
  )
{
  if (n > 0) {
    return nonnull;
  } else {
    return nonnull;
  }
}

INT32 *_Nonnull
NonnullReturn (
  INT32  *p
  )
{
  return p;
}

VOID
NonnullArg (
  INT32 *_Nonnull  p
  )
{
}

INT32
f6 (
  INT32  n
  )
{
  return __builtin_ctzll (n);
}

INT64
f7 (
  INT64  n
  )
{
  return __builtin_ctzll (n);
}

INT32
GetInt (
  INT32 *const  p __attribute__ ((pass_object_size (0))),
  INT32         i
  )
{
  return p[i];
}

INT32
GetFloat (
  float *const  p __attribute__ ((pass_object_size (0))),
  INT32         i
  )
{
  return p[i];
}

INT32
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
BoundsCheck (
  VOID
  )
{
  INT32  Bar[2], i = 2, j = 3, k = 4;

  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with bounds...\n\n\n"));

  GetInt (Bar, i);
  DEBUG ((DEBUG_WARN, "UBT: Index 2 out of bounds for type \'INT32 *\'...\n\n"));

  /*
    float baz[2];
    GetFloat(baz, i);
    DEBUG((DEBUG_WARN, "UBT: Index 2 out of bounds for type \'float
    *\'...\n\n"));
  */

  GetIntFromMultidemArr (i, j - 1, k - 1);
  DEBUG (
         (DEBUG_WARN,
          "UBT: Index 2 out of bounds for type \'INT32[2][3][4]\'...\n\n")
         );
  GetIntFromMultidemArr (i - 1, j, k - 1);
  DEBUG (
         (DEBUG_WARN,
          "UBT: Index 2 out of bounds for type \'INT32[3][4]\'...\n\n")
         );
  GetIntFromMultidemArr (i - 1, j - 1, k);
  DEBUG (
         (DEBUG_WARN, "UBT: Index 2 out of bounds for type \'INT32[4]\'...\n\n")
         );

  DEBUG ((DEBUG_INFO, "\nUBT: DONE...\n\n\n\n\n"));
}

VOID
NonnullCheck (
  VOID
  )
{
  INT32  *p = 0;

  DEBUG (
         (DEBUG_INFO, "UBT: Start testing cases with nonnull atribute...\n\n\n")
         );

  f1 (p, 8);
  DEBUG (
         (DEBUG_WARN,
          "UBT: Null pointer passed as argument 1, which is declared to never "
          "be null...\n\n")
         );
  // f2 (8, p);
  // DEBUG (
  //        (DEBUG_WARN,
  //         "UBT: Null pointer passed as argument 2, which is declared to never "
  //         "be null...\n\n")
  //        );

  f3 (p);
  DEBUG (
         (DEBUG_WARN,
          "UBT: Null pointer returned from function declared to never return "
          "null...\n\n")
         );
  f4 (p, 8);
  DEBUG (
         (DEBUG_WARN,
          "UBT: Null pointer returned from function declared to never return "
          "null...\n\n")
         );
  f4 (p, -8);
  DEBUG (
         (DEBUG_WARN,
          "UBT: Null pointer returned from function declared to never return "
          "null...\n\n")
         );

  NonnullReturn (NULL);
  DEBUG (
         (DEBUG_WARN,
          "UBT: Null pointer returned from function declared to never return "
          "null... (_Nonnull)\n\n")
         );
  NonnullArg (p);
  DEBUG (
         (DEBUG_WARN,
          "UBT: Null pointer passed as argument 1, which is declared to never "
          "be null... (_Nonnull)\n\n")
         );

  DEBUG ((DEBUG_INFO, "\nUBT: DONE...\n\n\n\n\n"));
}

VOID
ShiftOutOfBoundsCheck (
  VOID
  )
{
  UINT16  p = 1;

  DEBUG (
         (DEBUG_INFO,
          "UBT: Start testing cases with shift out of bounds...\n\n\n")
         );

  INT32  i = 32;

  p >>= i;
  DEBUG (
         (DEBUG_WARN, "UBT: Shift exponent 32 is too large for 16-bit type\n\n")
         );

  p   = 1;
  i   = -1;
  p >>= i;
  DEBUG ((DEBUG_WARN, "UBT: Shift exponent -1 is negative\n\n"));

  p   = 1;
  i   = 32;
  p <<= i;
  DEBUG (
         (DEBUG_WARN, "UBT: Shift exponent 32 is too large for 16-bit type\n\n")
         );

  p   = 1;
  i   = -1;
  p <<= i;
  DEBUG ((DEBUG_WARN, "UBT: Shift exponent -1 is negative\n\n"));

  i = 31;
  i = 1 << i;
  DEBUG (
         (DEBUG_WARN,
          "UBT: Left shift of 1 by 31 places cannot be represented in 32-bit "
          "type \n\n")
         );

  INT32  q = -1;

  i   = 5;
  q <<= i;
  DEBUG ((DEBUG_WARN, "UBT: Left shift of negative value -1\n\n"));

  DEBUG ((DEBUG_INFO, "\nUBT: DONE...\n\n\n\n\n"));
}

/*
 VOID
 BuiltinCheck (
   VOID
   )
 {
   DEBUG ((DEBUG_INFO, "UBT: Start testing cases with builtin...\n\n\n"));
   f6 (0);
   f7 (0);
   DEBUG ((DEBUG_INFO, "\nUBT: DONE...\n\n\n\n\n"));
 }
*/
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  // missingReturn(); -Werror,-Wreturn-type

  NonnullCheck ();
  ShiftOutOfBoundsCheck ();
  BoundsCheck ();
  PointerCheck (); // abort after tests

  /*
    Implicit conversion + Integer
    Doesnt work with the tests above
  */
  // CheckConvertArithmeticsValue ();

  // BuiltinCheck(); works but after abort

  // INT16 (*f) (INT16); -Wincompatible-function-pointer-types
  // f = f6;

  return EFI_SUCCESS;
}
