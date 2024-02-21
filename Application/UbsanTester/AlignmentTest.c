#include "UbsanTester.h"

typedef INT8 *__attribute__ ((align_value (0x8000))) AlignedChar;

struct AcStruct {
  AlignedChar    a;
};

INT8 *
LoadFromAcStruct (
  struct AcStruct  *x
  )
{
  return x->a;
}

INT8 *
EFIAPI
Passthrough0 (
  __attribute__ ((align_value (0x8000))) INT8  *x
  )
{
  return x;
}

INT8 *
EFIAPI
__attribute__ ((alloc_align (2)))
Passthrough1 (
  INT8          *x,
  CONST UINT32  Alignment
  )
{
  return x;
}

INT8 *
EFIAPI
__attribute__ ((assume_aligned (0x8000, 1)))
Passthrough2 (
  INT8  *x
  )
{
  return x;
}

VOID
EFIAPI
PointerAlignmentCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with pointer alignment...\n"));
  INT8  *Ptr = AllocateZeroPool (2);
  VOID  *Res;

  struct AcStruct  x;

  x.a = Ptr + 1;
  LoadFromAcStruct (&x); // why offsey 0x0?
  DEBUG ((DEBUG_WARN, "UBT: Alignment assumption of 0x8000 for pointer 0x%lx\n\n", Ptr + 0x1));

  Passthrough0 (Ptr + 1);
  DEBUG ((DEBUG_WARN, "UBT: Alignment assumption of 0x8000 for pointer 0x%lx\n\n", Ptr + 0x1));

  Passthrough1 (Ptr + 2, 0x8000);
  DEBUG ((DEBUG_WARN, "UBT: Alignment assumption of 0x8000 for pointer 0x%lx\n\n", Ptr + 0x2));

  Res = __builtin_assume_aligned (Ptr + 2, 0x8000);
  DEBUG ((DEBUG_WARN, "UBT: Alignment assumption of 0x8000 for pointer 0x%lx\n\n", Ptr + 0x2));

  FreePool (Ptr);

  Ptr = AllocateZeroPool (3);
  Passthrough2 (Ptr + 2);
  DEBUG ((DEBUG_WARN, "UBT: Alignment assumption of 0x8000 for pointer 0x%lx\n\n", Ptr + 0x1)); // why Ptr + 1

  UINT32  Offset = 1;

  Res = __builtin_assume_aligned (Ptr + 2, 0x8000, Offset);
  DEBUG ((DEBUG_WARN, "UBT: Alignment assumption of 0x8000 for pointer 0x%lx\n\n\n\n", Ptr + 0x1));

  FreePool (Ptr);
  DEBUG ((DEBUG_INFO, "UBT: Checks with pointer alignment are done...\n\n\n\n\n"));
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
  INT32           k;
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
  INT32  n
  )
{
  INT8      c[] __attribute__ ((aligned (16))) = { 0, 0, 0, 0, 1, 2, 3, 4, 5, 0, 0, 0, 0, 1, 2, 3, 4, 5 };
  INT32     *p                                 = (INT32 *)&c[4 + n];
  struct S  *s                                 = (struct S *)p;

  switch (Type) {
    case 'l':
      return *p && 0;
    case 'L':
    {
      INT32  x;
      MyMemCpy (&x, p, sizeof (x));
      return x && 0;
    }
    case 's':
    {
      *p = 1;
      break;
    }
    case 'S':
    {
      INT32  x = 1;
      MyMemCpy (p, &x, sizeof (x));
      break;
    }
    case 'm':
    {
      return s->k && 0;
    }
    case 'f':
    {
      s->F = FMember;
      return s->F () && 0;
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
  DEBUG ((
          DEBUG_INFO,
          "UBT: Start testing cases with alignment...\n\n\n"
         ));
  Check ('l', 0); // Correct
  Check ('l', 1);
  DEBUG ((DEBUG_WARN, "UBT: Load of misaligned address [[PTR:0x[0-9a-f]*]] for type 'INT32' (aka 'int') which requires 4 byte alignment\n\n"));
  Check ('L', 1); // how to do this for CONST INT32 *
  DEBUG ((DEBUG_WARN, "UBT: Load of misaligned address [[PTR:0x[0-9a-f]*]] for type 'CONST INT32' (aka 'const int') which requires 4 byte alignment\n\n"));
  Check ('s', 1);
  DEBUG ((DEBUG_WARN, "UBT: Store to misaligned address [[PTR:0x[0-9a-f]*]] for type 'INT32' (aka 'int') which requires 4 byte alignment\n\n"));
  Check ('S', 1);
  DEBUG ((DEBUG_WARN, "UBT: Store to misaligned address [[PTR:0x[0-9a-f]*]] for type 'INT32' (aka 'int') which requires 4 byte alignment\n\n"));
  Check ('m', 1);
  DEBUG ((DEBUG_WARN, "UBT: Member access within misaligned address [[PTR:0x[0-9a-f]*]] for type 'struct S' which requires 8 byte alignment\n\n"));
  DEBUG ((DEBUG_WARN, "UBT: Load of misaligned address [[PTR:0x[0-9a-f]*]] for type 'INT32' (aka 'int') which requires 8 byte alignment\n\n"));
  Check ('f', 1);
  DEBUG ((DEBUG_WARN, "UBT: Member access within misaligned address [[PTR:0x[0-9a-f]*]] for type 'struct S' which requires 8 byte alignment\n\n"));
  DEBUG ((DEBUG_WARN, "UBT: Store to misaligned address [[PTR:0x[0-9a-f]*]] for type 'EFIAPI INT32 ((*))(void) __attribute__((ms_abi))' (aka 'int (*)(void) __attribute__((ms_abi))') which requires 8 byte alignment\n\n"));
  DEBUG ((DEBUG_WARN, "UBT: Member access within misaligned address [[PTR:0x[0-9a-f]*]] for type 'struct S' which requires 8 byte alignment\n\n"));
  DEBUG ((DEBUG_WARN, "UBT: Load of misaligned address [[PTR:0x[0-9a-f]*]] for type 'EFIAPI INT32 ((*))(void) __attribute__((ms_abi))' (aka 'int (*)(void) __attribute__((ms_abi))') which requires 8 byte alignment\n\n"));

  DEBUG ((DEBUG_INFO, "UBT: Checks with alignment are done...\n\n\n\n\n"));

  PointerAlignmentCheck ();
}
