#include "UbsanTester.h"

typedef INT8 *__attribute__ ((align_value (0x8000))) AlignedChar;

struct AcStruct {
  AlignedChar    A;
};

INT8 *
LoadFromAcStruct (
  struct AcStruct  *X
  )
{
  return X->A;
}

INT8 *
EFIAPI
Passthrough0 (
  __attribute__ ((align_value (0x8000))) INT8  *X
  )
{
  return X;
}

INT8 *
EFIAPI
__attribute__ ((alloc_align (2)))
Passthrough1 (
  INT8          *X,
  CONST UINT32  Alignment
  )
{
  return X;
}

INT8 *
EFIAPI
__attribute__ ((assume_aligned (0x8000, 1)))
Passthrough2 (
  INT8  *X
  )
{
  return X;
}

VOID
EFIAPI
PointerAlignmentCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "\nUBT: Start testing cases with pointer alignment...\n"));
  INT8  *Ptr = AllocateZeroPool (2);
  VOID  *Res;

  struct AcStruct  X;

  X.A = Ptr + 1;
  LoadFromAcStruct (&X);
  DEBUG ((DEBUG_WARN, "\nUBT: Alignment assumption of 0x8000 for pointer 0x%lx\n", Ptr + 0x1));

  Passthrough0 (Ptr + 1);
  DEBUG ((DEBUG_WARN, "\nUBT: Alignment assumption of 0x8000 for pointer 0x%lx\n", Ptr + 0x1));

  Passthrough1 (Ptr + 2, 0x8000);
  DEBUG ((DEBUG_WARN, "\nUBT: Alignment assumption of 0x8000 for pointer 0x%lx\n", Ptr + 0x2));

  Res = __builtin_assume_aligned (Ptr + 2, 0x8000);
  DEBUG ((DEBUG_WARN, "\nUBT: Alignment assumption of 0x8000 for pointer 0x%lx\n", Ptr + 0x2));

  FreePool (Ptr);

  Ptr = AllocateZeroPool (3);
  Passthrough2 (Ptr + 2);
  DEBUG ((DEBUG_WARN, "\nUBT: Alignment assumption of 0x8000 for pointer 0x%lx\n", Ptr + 0x1)); // why Ptr + 1

  UINT32  Offset = 1;

  Res = __builtin_assume_aligned (Ptr + 2, 0x8000, Offset);
  DEBUG ((DEBUG_WARN, "\nUBT: Alignment assumption of 0x8000 for pointer 0x%lx\n\n", Ptr + 0x1));

  FreePool (Ptr);
  DEBUG ((DEBUG_INFO, "\nUBT: Checks with pointer alignment are done...\n\n\n"));
}

INT32
EFIAPI
FMember (
  VOID
  )
{
  return 0;
}

struct S {
  INT32 EFIAPI    (*F) (
    VOID
    );
  INT32           K;
};

INT32 *
EFIAPI
MyMemCpy (
  INT32        *Dest,
  CONST INT32  *Src,
  INT32        Bytes
  )
{
  INT32        *BDest = Dest;
  CONST INT32  *BSrc  = Src;

  for (INT32 i = 0; i < Bytes / 4; ++i) {
    *(BDest++) = *(BSrc++);
  }

  return Dest;
}

INT32
EFIAPI
Check (
  INT8   Type,
  INT32  N
  )
{
  INT8      c[] __attribute__ ((aligned (16))) = { 0, 0, 0, 0, 1, 2, 3, 4, 5, 0, 0, 0, 0, 1, 2, 3, 4, 5 };
  INT32     *P                                 = (INT32 *)&c[4 + N];
  struct S  *S                                 = (struct S *)P;

  switch (Type) {
    case 'l':
      return *P && 0;
    case 'L':
    {
      INT32  X;
      MyMemCpy (&X, P, sizeof (X));
      return X && 0;
    }
    case 's':
    {
      *P = 1;
      break;
    }
    case 'S':
    {
      INT32  X = 1;
      MyMemCpy (P, &X, sizeof (X));
      break;
    }
    case 'm':
    {
      return S->K && 0;
    }
    case 'f':
    {
      S->F = FMember;
      return S->F () && 0;
    }
  }

  return 0;
}

VOID
EFIAPI
AlignmentCheck (
  VOID
  )
{
  DEBUG (
         (
          DEBUG_INFO,
          "\nUBT: Start testing cases with alignment...\n\n"
         )
         );
  Check ('l', 0); // Correct
  Check ('l', 1);
  DEBUG ((DEBUG_WARN, "\nUBT: Load of misaligned address [[PTR:0x[0-9a-f]*]] for type 'INT32' (aka 'int') which requires 4 byte alignment\n"));
  Check ('L', 1);
  DEBUG ((DEBUG_WARN, "\nUBT: Load of misaligned address [[PTR:0x[0-9a-f]*]] for type 'CONST INT32' (aka 'const int') which requires 4 byte alignment\n"));
  Check ('s', 1);
  DEBUG ((DEBUG_WARN, "\nUBT: Store to misaligned address [[PTR:0x[0-9a-f]*]] for type 'INT32' (aka 'int') which requires 4 byte alignment\n"));
  Check ('S', 1);
  DEBUG ((DEBUG_WARN, "\nUBT: Store to misaligned address [[PTR:0x[0-9a-f]*]] for type 'INT32' (aka 'int') which requires 4 byte alignment\n"));
  Check ('m', 1);
  DEBUG ((DEBUG_WARN, "\nUBT: Member access within misaligned address [[PTR:0x[0-9a-f]*]] for type 'struct S' which requires 8 byte alignment\n"));
  DEBUG ((DEBUG_WARN, "\nUBT: Load of misaligned address [[PTR:0x[0-9a-f]*]] for type 'INT32' (aka 'int') which requires 8 byte alignment\n"));
  Check ('f', 1);
  DEBUG ((DEBUG_WARN, "\nUBT: Member access within misaligned address [[PTR:0x[0-9a-f]*]] for type 'struct S' which requires 8 byte alignment\n"));
  DEBUG ((DEBUG_WARN, "\nUBT: Store to misaligned address [[PTR:0x[0-9a-f]*]] for type 'EFIAPI INT32 ((*))(void) __attribute__((ms_abi))' (aka 'int (*)(void) __attribute__((ms_abi))') which requires 8 byte alignment\n"));
  DEBUG ((DEBUG_WARN, "\nUBT: Load of misaligned address [[PTR:0x[0-9a-f]*]] for type 'EFIAPI INT32 ((*))(void) __attribute__((ms_abi))' (aka 'int (*)(void) __attribute__((ms_abi))') which requires 8 byte alignment\n"));

  DEBUG ((DEBUG_INFO, "\nUBT: Checks with alignment are done...\n\n\n"));

  PointerAlignmentCheck ();
}
