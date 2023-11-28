#include "UbsanTester.h"

STATIC INT8 *
EFIAPI
GetelementpointerInbounds (
  INT8    *Base,
  UINT64  Offset
  )
{
  return Base + Offset;
}

VOID
EFIAPI
PointerOverflowCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "UBT: Pointer overflow...\n\n\n"));

  INT8  *Base, *Result;

  Base   = (INT8 *)MAX_ADDRESS;
  Result = Base + 1;
  DEBUG ((
          DEBUG_WARN,
          "UBT: Applying non-zero offset to non-null pointer 0x%X produced null pointer\n\n",
          Base
         ));

  Base   = (INT8 *)MAX_ADDRESS;
  Result = Base + 2;
  DEBUG ((
          DEBUG_WARN,
          "UBT: Addition of unsigned offset from 0x%X overflowed to 0x%X\n\n",
          Base,
          Result
         ));

  Base   = (INT8 *)0;
  Result = Base + 0;

  DEBUG ((DEBUG_WARN, "UBT: Applying zero offset to null pointer\n\n"));

  Base   = (INT8 *)0;
  Result = Base + 1;
  DEBUG ((DEBUG_WARN, "UBT: Applying non-zero offset 1 to null pointer\n\n"));

  Base   = (INT8 *)1;
  Result = Base - 1;
  DEBUG ((
          DEBUG_WARN,
          "UBT: Applying non-zero offset to non-null pointer 0x%X produced null pointer\n\n",
          Base
         ));

  UINT64  Offset = 2ULL;

  Base    = (INT8 *)0;
  Offset -= -1;
  (VOID)GetelementpointerInbounds (Base, Offset);
  DEBUG ((DEBUG_WARN, "UBT: Applying zero offset to null pointer\n\n"));

  INT8  c;

  Base = &c;
  INT64  NegOffset = -1;

  Result = Base + NegOffset;  // doesn't work
  DEBUG ((
          DEBUG_WARN,
          "UBT: Addition of unsigned offset to 0x%X overflowed to 0x%X\n\n",
          Base,
          Result
         ));

  Result = Base - NegOffset;  // doesn't work
  DEBUG ((
          DEBUG_WARN,
          "UBT: Subtraction of unsigned offset from 0x%X overflowed to 0x%X\n\n",
          Base,
          Result
         ));

  Base   = NULL;
  Result = Base - 1ULL;
  DEBUG ((DEBUG_WARN, "UBT: Applying non-zero offset -1 to null pointer\n\n"));

  DEBUG ((DEBUG_INFO, "\nUBT: Pointer overflow checks are done...\n\n\n"));
}

INT32
EFIAPI
F (
  VOID
  )
{
  return 0;
}

struct S {
  INT32    (*F)(
    VOID
    );
  INT32    k;
};

INT32
EFIAPI
NullCheck0 (
  INT32  *p
  )
{
  return *p;
}

INT32
EFIAPI
NullCheck3 (
  VOID
  )
{
  INT32  q[] = { 0, 1 };

  q[3] = 2;
  return q[0];
}

INT32
EFIAPI
NullCheck1 (
  struct S  *s
  )
{
  return s->k;
}

VOID __attribute__ ((no_sanitize ("bounds")))
EFIAPI
NullPointerCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "UBT: Null pointer...\n\n"));
  INT32     *p = 0;
  struct S  *s = 0;

  (VOID)*p;  // ok!
  DEBUG ((DEBUG_WARN, "UBT: Everything is fine here\n\n"));

  NullCheck0 (p);
  DEBUG ((DEBUG_WARN, "UBT: Load of null pointer of type 'INT32'\n\n"));

  NullCheck1 (s);
  DEBUG ((DEBUG_WARN, "UBT: Member access within null pointer of type 'S'\n\n"));

  NullCheck3 ();
  DEBUG ((DEBUG_WARN, "UBT: Store to null pointer of type 'INT32'\n\n"));

  DEBUG ((DEBUG_INFO, "UBT: Checks with null pointer are done...\n\n\n\n\n"));
}

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
Passthrough0 (
  __attribute__ ((align_value (0x8000))) INT8  *x
  )
{
  return x;
}

INT8 *__attribute__ ((alloc_align (2)))
Passthrough1 (
  INT8          *x,
  CONST UINT32  Alignment
  )
{
  return x;
}

INT8 *__attribute__ ((assume_aligned (0x8000, 1)))
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
  DEBUG ((DEBUG_INFO, "UBT: Pointer alignment...\n"));
  INT8  *Ptr = AllocateZeroPool (2);
  VOID  *Res;

  struct AcStruct  x;

  x.a = Ptr + 1;
  LoadFromAcStruct (&x);
  DEBUG ((DEBUG_WARN, "UBT: Assumption of 32768 byte alignment for pointer 0x%lx of type 'AlignedChar' failed\n\n", Ptr));

  Passthrough0 (Ptr + 1);
  DEBUG ((DEBUG_WARN, "UBT: Assumption of 32768 byte alignment for pointer 0x%lx of type 'INT8 *' failed\n\n", Ptr));

  Passthrough1 (Ptr + 1, 0x8000);
  DEBUG ((DEBUG_WARN, "UBT: Assumption of 32768 byte alignment for pointer 0x%lx of type 'INT8 *' failed\n\n", Ptr));

  Res = __builtin_assume_aligned (Ptr + 2, 0x8000);
  DEBUG ((DEBUG_WARN, "UBT: Assumption of 32768 byte alignment for pointer 0x%lx of type 'INT8 *' failed\n\n", Ptr));

  FreePool (Ptr);

  Ptr = AllocateZeroPool (3);
  Passthrough2 (Ptr + 2);
  DEBUG ((DEBUG_WARN, "UBT: Assumption of 32768 byte alignment (with offset of 1 byte) for pointer 0x%lx of type 'INT8 *' failed\n\n", Ptr));

  UINT32  Offset = 1;

  Res = __builtin_assume_aligned (Ptr + 2, 0x8000, Offset);
  DEBUG ((DEBUG_WARN, "UBT: Assumption of 32768 byte alignment (with offset of 1 byte) for pointer 0x%lx of type 'INT8 *' failed\n\n", Ptr));

  FreePool (Ptr);
  DEBUG ((DEBUG_INFO, "UBT: Checks with pointer alignment are done...\n\n\n\n\n"));
}

VOID
EFIAPI
PointerCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with pointers...\n"));

  PointerOverflowCheck ();
  NullPointerCheck ();
  PointerAlignmentCheck ();
  DEBUG ((DEBUG_INFO, "UBT: Completing testing cases with pointers...\n\n\n\n\n"));
}
