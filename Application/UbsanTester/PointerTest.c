#include "UbsanTester.h"

STATIC INT8 *
GetelementpointerInbounds (
  INT8    *Base,
  UINT64  Offset
  )
{
  return Base + Offset;
}

VOID
PointerOverflowCheck (
  VOID
  )
{
  // mb need to separate code

  DEBUG ((DEBUG_WARN, "UBT: Pointer overflow\n\n\n"));

  INT8  *Base, *Result;

  Base   = (INT8 *)MAX_ADDRESS;
  Result = Base + 1;
  DEBUG (
         (DEBUG_WARN,
          "UBT: Applying non-zero offset to non-null pointer 0x%X produced null "
          "pointer\n\n",
          Base)
         );

  Base   = (INT8 *)MAX_ADDRESS;
  Result = Base + 2;
  DEBUG (
         (DEBUG_WARN,
          "UBT: Addition of unsigned offset from 0x%X overflowed to 0x%X\n\n",
          Base, Result)
         );

  Base   = (INT8 *)0;
  Result = Base + 0;

  DEBUG ((DEBUG_WARN, "UBT: Applying zero offset to null pointer\n\n"));

  Base   = (INT8 *)0;
  Result = Base + 1;
  DEBUG ((DEBUG_WARN, "UBT: Applying non-zero offset 1 to null pointer\n\n"));

  Base   = (INT8 *)1;
  Result = Base - 1;
  DEBUG (
         (DEBUG_WARN,
          "UBT: Applying non-zero offset to non-null pointer 0x%X produced null "
          "pointer\n\n",
          Base)
         );

  UINT64  Offset = 2ULL;

  Base    = (INT8 *)0;
  Offset -= -1;
  (VOID)GetelementpointerInbounds (Base, Offset);
  DEBUG ((DEBUG_WARN, "UBT: Applying zero offset to null pointer\n\n"));

  INT8  c;

  Base = &c;
  INT64  NegOffset = -1;

  Result = Base + NegOffset;  // doesn't work
  DEBUG (
         (DEBUG_WARN,
          "UBT: Addition of unsigned offset to 0x%X overflowed to 0x%X\n\n",
          Base, Result)
         );

  Result = Base - NegOffset;  // doesn't work
  DEBUG (
         (DEBUG_WARN,
          "UBT: Subtraction of unsigned offset from 0x%X overflowed to 0x%X\n\n",
          Base, Result)
         );

  Base   = NULL;
  Result = Base - 1ULL;
  DEBUG ((DEBUG_WARN, "UBT: Applying non-zero offset -1 to null pointer\n\n"));

  DEBUG ((DEBUG_INFO, "\nUBT: Pointer overflow checks are done.\n\n\n"));
}

INT32
f (
  VOID
  )
{
  return 0;
}

struct S {
  INT32    (*f)(
    VOID
    );
  INT32    k;
};

INT32
NullCheck0 (
  INT32  *p
  )
{
  return *p;
}

INT32
NullCheck3 (
  VOID
  )
{
  INT32  q[] = { 0, 1 };

  q[3] = 2;
  return q[0];
}

/*
  INT32* Check2 (INT32** p) {
      INT32 *r;
      r = *p;
      return r;
  }
*/
INT32
NullCheck1 (
  struct S  *s
  )
{
  return s->k;
}

VOID
NullPointerCheck (
  VOID
  )
{
  DEBUG ((DEBUG_WARN, "UBT: Null pointer...\n\n"));
  INT32     *p = 0;
  struct S  *s = 0;

  (VOID)*p;  // ok!
  DEBUG ((DEBUG_WARN, "UBT: Everything is fine here\n\n"));

  NullCheck0 (p);
  DEBUG ((DEBUG_WARN, "UBT: Load of null pointer of type 'INT32'\n\n"));

  NullCheck1 (s);
  DEBUG ((DEBUG_WARN, "UBT: Member access within null pointer of type 'S'\n\n"));

  /*
    Check2(q); Only in c++?
    DEBUG ((DEBUG_WARN, "UBT: Reference binding to null pointer of type
    'INT32'\n\n"));
  */

  NullCheck3 ();  // It works, but throws assert /:
  // *p = 1;
  DEBUG ((DEBUG_WARN, "UBT: Store to null pointer of type 'INT32'\n\n"));

  DEBUG ((DEBUG_INFO, "UBT: Checks with null pointer are done.\n\n\n\n\n"));
}

VOID
PointerCheck (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "UBT: Start testing cases with pointers...\n"));

  PointerOverflowCheck ();
  NullPointerCheck ();

  DEBUG (
         (DEBUG_INFO, "UBT: Completing testing cases with pointers...\n\n\n\n\n")
         );
}
